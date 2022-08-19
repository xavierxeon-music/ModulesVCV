#include "PamelasClock.h"
#include "PamelasClockPanel.h"

#include <SchweineSystemMaster.h>

PamelasClock::PamelasClock()
   : SchweineSystem::Module()
   , midiInput()
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , tickCounter(6)
   , doNotAdvanceTempo(false)
   , tempo()
   , clockTick()
   , tickTrigger()
   , clockReset()
   , resetTrigger()

{
   setup();

   connectionButton.setDefaultColor(SchweineSystem::Color{0, 255, 0});
   connectToMidiDevice();
}

void PamelasClock::process(const ProcessArgs& args)
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

void PamelasClock::processMessage(const midi::Message& msg)
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
}

void PamelasClock::connectToMidiDevice()
{
   midiInput.reset();
   connectionButton.setOff();

   static const std::string targetDeviceName = SchweineSystem::Common::midiInterfaceMap.at(Midi::Device::Pamela);
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

PamelasClockWidget::PamelasClockWidget(PamelasClock* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelPamelasClock = SchweineSystem::Master::the()->addModule<PamelasClock, PamelasClockWidget>("PamelasClock");
