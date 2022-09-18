#include "MetropolixClock.h"

#include <SvinOrigin.h>

#include <Midi/MidiCommon.h>
#include <SvinMidi.h>

MetropolixClock::MetropolixClock()
   : Svin::Module()
   , Svin::Midi::Input(Midi::Device::Metropolix)
   , Svin::MasterClock()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , midiTickCounter(6)
   , advanceTempo(true)
   , resetOutput(this, Panel::Reset)
   , clockInput(this, Panel::Override_Clock)
   , resetInput(this, Panel::Override_Reset)
   , displayController(this, Panel::Pixels_Display)
{
   setup();

   connectionButton.setDefaultColor(Svin::Color{0, 255, 0});
   connectToMidiDevice();
}

void MetropolixClock::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (clockInput.isConnected()) // override
   {
      if (resetInput.isTriggered())
      {
         reset();
         advanceTempo = false;
         midiTickCounter.reset();
         resetOutput.trigger();
      }
      else if (clockInput.isTriggered())
      {
         tick();
         advanceTempo = false;
      }
   }

   if (advanceTempo)
      advance(args.sampleRate);

   resetOutput.animateTriggers(args);
   advanceTempo = true;
}

void MetropolixClock::updateDisplays()
{
   displayController.fill();

   displayController.drawRect(0, 0, 82, 10, true);
   displayController.drawRect(0, 95, 82, 105, true);
   displayController.drawRect(0, 135, 82, 145, true);

   displayController.setColor(Svin::Color{0, 0, 0});
   displayController.writeText(1, 1, "counter", Svin::DisplayOLED::Font::Normal);
   displayController.writeText(1, 96, "tempo", Svin::DisplayOLED::Font::Normal);
   displayController.writeText(1, 136, "time", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Svin::Color{255, 255, 255});

   TimeCode timeCode(getDuration());

   // counter
   displayController.writeText(1, 15, "bar", Svin::DisplayOLED::Font::Normal);
   displayController.writeText(41, 30, std::to_string(timeCode.bar), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);

   displayController.writeText(1, 65, "rest", Svin::DisplayOLED::Font::Small);
   const std::string rest = std::to_string(timeCode.quarter) + '.' + std::to_string(timeCode.tick);
   displayController.writeText(41, 75, rest, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   // tempo
   const uint8_t bpm = getTempo().getBeatsPerMinute();
   displayController.writeText(41, 110, std::to_string(bpm), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

   // time
   const float secondsPerTick = 60.0 / (4.0 * bpm);
   const uint32_t totalSeconds = static_cast<uint32_t>(getDuration() * secondsPerTick);
   const uint8_t seconds = totalSeconds % 60;
   const uint32_t minutes = (totalSeconds - seconds) / 60;

   std::string secondText = std::to_string(seconds);
   if (seconds < 10)
      secondText = "0" + secondText;

   const std::string timeText = std::to_string(minutes) + ":" + secondText;
   displayController.writeText(41, 150, timeText, Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);
}

void MetropolixClock::connectToMidiDevice()
{
   if (connected())
   {
      connectionButton.setOn();
      return;
   }

   connectionButton.setOff();
   if (!open())
      return;

   connectionButton.setOn();
}

void MetropolixClock::clockTick()
{
   midiClock();
   if (0 != midiTickCounter.valueAndNext())
      return;

   tick();
   advanceTempo = false;
}

void MetropolixClock::songPosition(const uint16_t position)
{
   if (0 != position)
      return;

   reset();
   advanceTempo = false;
   midiTickCounter.reset();
   resetOutput.trigger();
}

// widget

MetropolixClockWidget::MetropolixClockWidget(MetropolixClock* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// creete module
Model* modelMetropolixClock = Svin::Origin::the()->addModule<MetropolixClock, MetropolixClockWidget>("MetropolixClock");

