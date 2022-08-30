#include "Display.h"

#include <Tools/Convert.h>
#include <Tools/Variable.h>

#include <SvinMasterClock.h>

#include "../TrackerWorker.h"
#include "../TrackerWorkerPanel.h"

Display::Display(TrackerWorker* main)
   : main(main)
   , controller(main, TrackerWorker::Panel::Pixels_Display)
{
   controller.onClicked(this, &Display::displayClicked);
}

void Display::update()
{
   controller.fill();

   if (TrackerWorker::OperationMode::Passthrough == main->operationMode)
      updatePassthrough();
   else if (TrackerWorker::OperationMode::Remote == main->operationMode)
      updateRemote();
   else if (TrackerWorker::OperationMode::InternalOverview == main->operationMode)
      updateInternalOverview();
   else if (TrackerWorker::OperationMode::InternalCurrent == main->operationMode)
      updateInternalCurrent();
}

void Display::updatePassthrough()
{
   controller.setColor(Svin::Color{0, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Passthrough", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});

   const Tempo tempo = main->getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const float voltage = main->inputList[groupIndex]->getVoltage(channelIndex);
         const uint8_t value = main->voltageToValue(voltage);
         const std::string valueText = on ? Convert::text(value) : "off";
         controller.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void Display::updateRemote()
{
   controller.setColor(Svin::Color{0, 255, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Remote", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});

   const Tempo tempo = main->getTempo();
   const bool on = tempo.isRunningOrFirstTick();

   for (uint8_t channelIndex = 0; channelIndex < 16; channelIndex++)
   {
      const uint8_t y = 15 + 10 * channelIndex;

      for (uint8_t groupIndex = 0; groupIndex < 2; groupIndex++)
      {
         const uint8_t x = 50 + groupIndex * 40;

         const uint8_t value = main->remoteValues[16 * groupIndex + channelIndex];
         const std::string valueText = on ? Convert::text(value) : "off";
         controller.writeText(x, y, valueText, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Right);
      }
   }
}

void Display::updateInternalOverview()
{
   controller.setColor(Svin::Color{255, 255, 0});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Overview", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});
   controller.writeText(0, 175, main->fileName, 3);

   const uint32_t segmentCount = main->project.getSegementCount();
   controller.writeText(5, 15, std::to_string(segmentCount) + " segments", Svin::DisplayOLED::Font::Normal);

   const std::string divName = Tempo::getName(main->project.getDivison());
   controller.writeText(5, 30, "@ " + divName, Svin::DisplayOLED::Font::Normal);

   const uint32_t index = main->project.getCurrentSegmentIndex();
   if (index < main->project.getSegementCount())
   {
      controller.writeText(50, 70, std::to_string(index), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);

      const std::string eventName = main->eventNameList.at(index);
      const std::string eventText = eventName.empty() ? "--" : eventName;
      controller.writeText(50, 100, eventText, Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);
   }
   else
   {
      controller.setColor(Svin::Color{255, 255, 0});
      controller.writeText(50, 70, "END", Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);
   }
}

void Display::updateInternalCurrent()
{
   controller.setColor(Svin::Color{255, 0, 255});
   controller.drawRect(0, 0, 100, 10, true);

   controller.setColor(Svin::Color{0, 0, 0});
   controller.writeText(50, 0, "Current", Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   controller.setColor(Svin::Color{255, 255, 255});
   controller.writeText(0, 15, "Hello", Svin::DisplayOLED::Font::Normal);
}

void Display::displayClicked(const float& x, const float& y)
{
   (void)x;
   (void)y;

   main->loadProject(main->getOpenFileName("Projects:json"));
}
