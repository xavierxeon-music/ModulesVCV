#include "ClockAndBarCounter.h"

#include <SvinOrigin.h>

#include <Midi/MidiCommon.h>
#include <SvinMidi.h>

ClockAndBarCounter::ClockAndBarCounter()
   : Svin::Module()
   , Svin::MidiInput(Midi::Device::Metropolix)
   , Svin::MasterClock()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , midiTickCounter(6)
   , blockAdvanceTempo(false)
   , runOutput(this, Panel::Running)
   , clockOutput(this, Panel::Clock)
   , resetOutput(this, Panel::Reset)
   , clockInput(this, Panel::Override_Clock)
   , resetInput(this, Panel::Override_Reset)
   , displayController(this, Panel::Pixels_Display)
{
   setup();

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToMidiDevice();
}

ClockAndBarCounter::~ClockAndBarCounter()
{
}

void ClockAndBarCounter::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (clockInput.isConnected()) // override midi clock
   {
      if (resetInput.isTriggered())
      {
         Svin::MasterClock::reset();
         blockAdvanceTempo = true;
         midiTickCounter.reset();
         resetOutput.trigger();
      }
      else if (clockInput.isTriggered())
      {
         tick();
         clockOutput.trigger();
         blockAdvanceTempo = true;
      }

      if (!blockAdvanceTempo)
      {
         const float percentage = getTempo().getPercentage();
         const float target = (1 + midiTickCounter.getCurrentValue()) / 6.0;
         if (percentage >= target)
         {
            midiClock();
            midiTickCounter.nextAndIsMaxValue();
         }
         advance(args.sampleRate);
      }
   }
   else // use midi clock
   {
      if (!blockAdvanceTempo)
         advance(args.sampleRate);
   }

   runOutput.setActive(getTempo().isRunningOrFirstTick());
   clockOutput.animateTriggers(args);
   resetOutput.animateTriggers(args);

   blockAdvanceTempo = false;
}

void ClockAndBarCounter::updateDisplays()
{
   displayController.fill();

   displayController.drawRect(0, 0, 82, 10, true);
   displayController.drawRect(0, 95, 82, 105, true);
   displayController.drawRect(0, 135, 82, 145, true);

   displayController.setColor(Color::Predefined::Black);
   displayController.writeText(1, 1, "counter", Svin::DisplayOLED::Font::Normal);
   displayController.writeText(1, 96, "tempo", Svin::DisplayOLED::Font::Normal);
   displayController.writeText(1, 136, "time", Svin::DisplayOLED::Font::Normal);

   displayController.setColor(Color::Predefined::White);

   TimeCode timeCode(getDuration());

   // counter
   displayController.writeText(1, 15, "bar", Svin::DisplayOLED::Font::Normal);
   displayController.writeText(41, 30, std::to_string(timeCode.bar + 1), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);

   displayController.writeText(1, 65, "rest", Svin::DisplayOLED::Font::Small);
   const std::string rest = std::to_string(timeCode.quarter + 1) + '.' + std::to_string(timeCode.tick + 1);
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

void ClockAndBarCounter::connectToMidiDevice()
{
   if (Svin::MidiInput::connected())
   {
      connectionButton.setOn();
      return;
   }

   connectionButton.setOff();
   if (!Svin::MidiInput::open())
      return;

   connectionButton.setOn();
}

void ClockAndBarCounter::clockTick()
{
   if (clockInput.isConnected())
      return;

   midiClock();
   if (0 != midiTickCounter.valueAndNext())
      return;

   tick();
   blockAdvanceTempo = true;

   clockOutput.trigger();
}

void ClockAndBarCounter::songPosition(const uint16_t& position)
{
   if (clockInput.isConnected())
      return;

   if (0 != position)
      return;

   Svin::MasterClock::reset();
   blockAdvanceTempo = true;

   midiTickCounter.reset();
   resetOutput.trigger();
}

// widget

ClockAndBarCounterWidget::ClockAndBarCounterWidget(ClockAndBarCounter* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// create module
Model* modelClockAndBarCounter = Svin::Origin::the()->addModule<ClockAndBarCounter, ClockAndBarCounterWidget>("ClockAndBarCounter");
