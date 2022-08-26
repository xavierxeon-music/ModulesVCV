#include "MetropolixClock.h"
#include "MetropolixClockPanel.h"

#include <SyMaster.h>

#include <Midi/MidiCommon.h>
#include <SyMidiOutput.h>

MetropolixClock::MetropolixClock()
   : Sy::Module()
   , midiInput()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , tickCounter(6)
   , doNotAdvanceTempo(false)
   , tempo()
   , clockTick()
   , clockReset()
{
   setup();

   connectionButton.setDefaultColor(Sy::Color{0, 255, 0});
   connectToMidiDevice();
}

void MetropolixClock::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   midi::Message msg;
   while (midiInput.tryPop(&msg, args.frame))
      processMessage(msg);

   if (doNotAdvanceTempo)
      doNotAdvanceTempo = false;
   else
      tempo.advance(args.sampleRate);

   outputs[Panel::Clock].setVoltage(clockTick.process(args.sampleTime) ? 10.f : 0.f);
   outputs[Panel::Reset].setVoltage(clockReset.process(args.sampleTime) ? 10.f : 0.f);
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
         clockTick.trigger();
         doNotAdvanceTempo = true;
      }
   }
   else if (Midi::Event::Start == event)
   {
      tickCounter.reset();
      tempo.clockReset();
      clockReset.trigger();
      doNotAdvanceTempo = true;
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
         clockReset.trigger();
         doNotAdvanceTempo = true;
      }
   }
}

void MetropolixClock::connectToMidiDevice()
{
   midiInput.reset();
   connectionButton.setOff();

   static const std::string targetDeviceName = Sy::Common::midiInterfaceMap.at(Midi::Device::Metropolix);
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
   : Sy::ModuleWidget(module)
{
   setup();
}

Model* modelMetropolixClock = Sy::Master::the()->addModule<MetropolixClock, MetropolixClockWidget>("MetropolixClock");
