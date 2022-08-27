#include "MetropolixClock.h"
#include "MetropolixClockPanel.h"

#include <SvinMaster.h>

#include <Midi/MidiCommon.h>
#include <SvinMidiOutput.h>

MetropolixClock::MetropolixClock()
   : Svin::Module()
   , midiInput()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , tickCounter(6)
   , doNotAdvanceTempo(false)
   , tempo()
   , clockOutput(this, Panel::Clock)
   , resetOutput(this, Panel::Reset)
   , clockInput(this, Panel::Override_Clock)
   , resetInput(this, Panel::Override_Reset)
   , duration(0)
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
      const bool isClock = clockInput.isTriggered();
      const bool isReset = resetInput.isTriggered();

      if (isReset)
      {
         duration = 0;
         tempo.clockReset();
         resetOutput.trigger();
      }
      else if (isClock)
      {
         duration++;
         tempo.clockTick();
         clockOutput.trigger();
      }
      else
         tempo.advance(args.sampleRate);
   }
   else
   {
      midi::Message msg;
      while (midiInput.tryPop(&msg, args.frame))
         processMessage(msg);

      if (doNotAdvanceTempo)
         doNotAdvanceTempo = false;
      else
         tempo.advance(args.sampleRate);
   }

   clockOutput.animateTriggers(args);
   resetOutput.animateTriggers(args);
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

   TimeCode timeCode(duration);

   // counter
   displayController.writeText(1, 15, "bar", Svin::DisplayOLED::Font::Normal);
   displayController.writeText(41, 30, std::to_string(timeCode.bar), Svin::DisplayOLED::Font::Huge, Svin::DisplayOLED::Alignment::Center);

   displayController.writeText(1, 65, "rest", Svin::DisplayOLED::Font::Small);
   const std::string rest = std::to_string(timeCode.quarter) + '.' + std::to_string(timeCode.tick);
   displayController.writeText(41, 75, rest, Svin::DisplayOLED::Font::Normal, Svin::DisplayOLED::Alignment::Center);

   // tempo
   const uint8_t bpm = tempo.getBeatsPerMinute();
   displayController.writeText(41, 110, std::to_string(bpm), Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);

   // time
   const float secondsPerTick = 60.0 / (4.0 * bpm);
   const uint32_t totalSeconds = static_cast<uint32_t>(duration * secondsPerTick);
   const uint8_t seconds = totalSeconds % 60;
   const uint32_t minutes = (totalSeconds - seconds) / 60;

   std::string secondText = std::to_string(seconds);
   if (seconds < 10)
      secondText = "0" + secondText;

   const std::string timeText = std::to_string(minutes) + ":" + secondText;
   displayController.writeText(41, 150, timeText, Svin::DisplayOLED::Font::Large, Svin::DisplayOLED::Alignment::Center);
}

void MetropolixClock::processMessage(const midi::Message& msg)
{
   const bool isSystemEvent = (0xF0 == (msg.bytes[0] & 0xF0));
   if (!isSystemEvent)
      return;

   const Midi::Event event = static_cast<Midi::Event>(msg.bytes[0]);

   if (Midi::Event::Clock == event)
   {
      if (0 == tickCounter.valueAndNext())
      {
         tempo.clockTick();
         clockOutput.trigger();
         doNotAdvanceTempo = true;
         duration++;
      }
   }
   else if (Midi::Event::SongPositionPointer == event)
   {
      const uint8_t frontByte = msg.bytes[0];
      const uint8_t backByte = msg.bytes[1];
      const uint16_t position = frontByte * 128 + backByte;

      if (30976 == position) // metropolix magix ?
      {
         tickCounter.reset();
         tempo.clockReset();
         resetOutput.trigger();
         doNotAdvanceTempo = true;
         duration = 0;
      }
   }
}

void MetropolixClock::connectToMidiDevice()
{
   midiInput.reset();
   connectionButton.setOff();

   static const std::string targetDeviceName = Svin::Common::midiInterfaceMap.at(Midi::Device::Metropolix);
   std::cout << targetDeviceName << std::endl;

   for (const int& deviceId : midiInput.getDeviceIds())
   {
      const std::string deviceName = midiInput.getDeviceName(deviceId);
      // std::cout << deviceName << std::endl;

      if (targetDeviceName == deviceName)
      {
         std::cout << "connected to " << deviceName << " @ " << deviceId << std::endl;
         midiInput.setDeviceId(deviceId);
         connectionButton.setOn();
         return;
      }
   }
}

// widget

MetropolixClockWidget::MetropolixClockWidget(MetropolixClock* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelMetropolixClock = Svin::Master::the()->addModule<MetropolixClock, MetropolixClockWidget>("MetropolixClock");