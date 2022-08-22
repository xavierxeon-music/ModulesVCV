#include "BarCounter.h"
#include "BarCounterPanel.h"

#include <SyMaster.h>
#include <Tools/Convert.h>

BarCounter::BarCounter()
   : Sy::Module()
   // tempo
   , clockTrigger()
   , resetTrigger()
   , tempo()
   // time
   , duration(0)
   , displayController(this, Panel::Pixels_Display)
{
   setup();
}

void BarCounter::process(const ProcessArgs& args)
{
   // clock
   const bool isClock = clockTrigger.process(inputs[Panel::Clock].getVoltage() > 3.0);
   const bool isReset = resetTrigger.process(inputs[Panel::Reset].getVoltage() > 3.0);

   if (isReset)
   {
      duration = 0;
      tempo.clockReset();
   }
   else if (isClock)
   {
      duration++;
      tempo.clockTick();
   }
   else
      tempo.advance(args.sampleRate);
}

void BarCounter::updateDisplays()
{
   displayController.fill();

   displayController.drawRect(0, 0, 82, 10, true);
   displayController.drawRect(0, 95, 82, 105, true);
   displayController.drawRect(0, 135, 82, 145, true);

   displayController.setColor(Sy::Color{0, 0, 0});
   displayController.writeText(1, 1, "counter", Sy::DisplayOLED::Font::Normal);
   displayController.writeText(1, 96, "tempo", Sy::DisplayOLED::Font::Normal);
   displayController.writeText(1, 136, "time", Sy::DisplayOLED::Font::Normal);

   displayController.setColor(Sy::Color{255, 255, 255});

   TimeCode timeCode(duration);

   // counter
   displayController.writeText(1, 15, "bar", Sy::DisplayOLED::Font::Normal);
   displayController.writeText(41, 30, std::to_string(timeCode.bar), Sy::DisplayOLED::Font::Huge, Sy::DisplayOLED::Alignment::Center);

   displayController.writeText(1, 65, "rest", Sy::DisplayOLED::Font::Small);
   const std::string rest = std::to_string(timeCode.quarter) + '.' + std::to_string(timeCode.tick);
   displayController.writeText(41, 75, rest, Sy::DisplayOLED::Font::Normal, Sy::DisplayOLED::Alignment::Center);

   // tempo
   const uint8_t bpm = tempo.getBeatsPerMinute();
   displayController.writeText(41, 110, std::to_string(bpm), Sy::DisplayOLED::Font::Large, Sy::DisplayOLED::Alignment::Center);

   // time
   const float secondsPerTick = 60.0 / (4.0 * bpm);
   const uint32_t totalSeconds = static_cast<uint32_t>(duration * secondsPerTick);
   const uint8_t seconds = totalSeconds % 60;
   const uint32_t minutes = (totalSeconds - seconds) / 60;

   std::string secondText = std::to_string(seconds);
   if (seconds < 10)
      secondText = "0" + secondText;

   const std::string timeText = std::to_string(minutes) + ":" + secondText;
   displayController.writeText(41, 150, timeText, Sy::DisplayOLED::Font::Large, Sy::DisplayOLED::Alignment::Center);
}

// widget

BarCounterWidget::BarCounterWidget(BarCounter* module)
   : Sy::ModuleWidget(module)
{
   setup();
}

Model* modelBarCounter = Sy::Master::the()->addModule<BarCounter, BarCounterWidget>("BarCounter");
