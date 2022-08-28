#include "Display.h"

#include <Tools/Convert.h>
#include <Tools/Variable.h>

#include "../TrackerWorker.h"
#include "../TrackerWorkerPanel.h"

Display::Display(TrackerWorker* main)
   : main(main)
   , displayMode(Mode::StageIndex)
   , displayButton(main, TrackerWorker::Panel::Display)
   , displayController(main, TrackerWorker::Panel::Pixels_Display)

{
}

void Display::process(const Module::ProcessArgs& args)
{
   // screen mode
   if (displayButton.isTriggered())
   {
      static const std::vector<Mode> order = {Mode::Division, Mode::Length, Mode::StageCount, Mode::StageIndex};
      Variable::Enum<Mode> variable(displayMode, order, true);
      variable.increment();
   }
}

void Display::update()
{
   displayController.fill();

   if (TrackerWorker::OperationMode::Passthrough == main->operationMode)
      updatePassthrough();
   else if (TrackerWorker::OperationMode::Remote == main->operationMode)
      updateRemote();
   else if (TrackerWorker::OperationMode::Internal == main->operationMode)
      updateInternal();
}

void Display::updatePassthrough()
{
   displayController.setColor(Svin::Color{0, 255, 0});
   displayController.drawRect(0, 0, 100, 10, true);

   displayController.setColor(Svin::Color{0, 0, 0});
   displayController.writeText(5, 1, "Passthrough", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{0, 255, 0});

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const float voltage = main->inputList[groupIndex]->getVoltage(channelIndex);
         const uint8_t value = main->voltageToValue(voltage);
         const std::string valueText = main->tempo.isRunningOrFirstTick() ? Convert::text(value) : "off";
         displayController.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void Display::updateRemote()
{
   displayController.setColor(Svin::Color{0, 255, 255});
   displayController.drawRect(0, 0, 100, 10, true);

   displayController.setColor(Svin::Color{0, 0, 0});
   displayController.writeText(5, 1, "Remote", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{0, 255, 255});

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const uint8_t value = main->remoteValues[16 * groupIndex + channelIndex];
         const std::string valueText = main->tempo.isRunningOrFirstTick() ? Convert::text(value) : "off";
         displayController.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void Display::updateInternal()
{
   displayController.setColor(Svin::Color{255, 255, 255});
   displayController.drawRect(0, 0, 100, 10, true);

   displayController.setColor(Svin::Color{0, 0, 0});

   if (Mode::Division == displayMode)
      displayController.writeText(5, 1, "Step", Svin::DisplayOLED::Font::Normal);
   else if (Mode::Length == displayMode)
      displayController.writeText(5, 1, "Length", Svin::DisplayOLED::Font::Normal);
   else if (Mode::StageCount == displayMode)
      displayController.writeText(5, 1, "Count", Svin::DisplayOLED::Font::Normal);
   else
      displayController.writeText(5, 1, "Current", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{255, 255, 255});

   displayController.writeText(5, 20, "Hello", Svin::DisplayOLED::Font::Normal);
}
