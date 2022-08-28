#include "Display.h"

#include <osdialog.h>

#include <Tools/Convert.h>
#include <Tools/Variable.h>

#include "../TrackerWorker.h"
#include "../TrackerWorkerPanel.h"

Display::Display(TrackerWorker* main)
   : main(main)
   , displayMode(Mode::StageIndex)
   , displayButton(main, TrackerWorker::Panel::Display)
   , controller(main, TrackerWorker::Panel::Pixels_Display)
{
   controller.onClicked(this, &Display::displayClicked);
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
   controller.fill();

   if (TrackerWorker::OperationMode::Passthrough == main->operationMode)
      updatePassthrough();
   else if (TrackerWorker::OperationMode::Remote == main->operationMode)
      updateRemote();
   else if (TrackerWorker::OperationMode::Internal == main->operationMode)
      updateInternal();
}

void Display::updatePassthrough()
{
   controller.setColor(Svin::Color{0, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(5, 1, "Passthrough", Svin::DisplayOLED::Font::Normal);

   controller.setColor(Svin::Color{0, 255, 0});

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const float voltage = main->inputList[groupIndex]->getVoltage(channelIndex);
         const uint8_t value = main->voltageToValue(voltage);
         const std::string valueText = main->tempo.isRunningOrFirstTick() ? Convert::text(value) : "off";
         controller.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void Display::updateRemote()
{
   controller.setColor(Svin::Color{0, 255, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(5, 1, "Remote", Svin::DisplayOLED::Font::Normal);

   controller.setColor(Svin::Color{0, 255, 255});

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const uint8_t value = main->remoteValues[16 * groupIndex + channelIndex];
         const std::string valueText = main->tempo.isRunningOrFirstTick() ? Convert::text(value) : "off";
         controller.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void Display::updateInternal()
{
   controller.setColor(Svin::Color{255, 255, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});

   if (Mode::Division == displayMode)
      controller.writeText(5, 1, "Step", Svin::DisplayOLED::Font::Normal);
   else if (Mode::Length == displayMode)
      controller.writeText(5, 1, "Length", Svin::DisplayOLED::Font::Normal);
   else if (Mode::StageCount == displayMode)
      controller.writeText(5, 1, "Count", Svin::DisplayOLED::Font::Normal);
   else
      controller.writeText(5, 1, "Current", Svin::DisplayOLED::Font::Normal);

   controller.setColor(Svin::Color{255, 255, 255});

   controller.writeText(5, 20, "Hello", Svin::DisplayOLED::Font::Normal);
}

void Display::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   const char* path = osdialog_file(OSDIALOG_OPEN, nullptr, NULL, osdialog_filters_parse("Projects:json"));
   if (path)
      main->loadProject(std::string(path));
}
