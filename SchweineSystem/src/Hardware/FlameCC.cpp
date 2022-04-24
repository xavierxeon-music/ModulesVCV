#include "FlameCC.h"
#include "FlameCCPanel.h"

#include <Midi/MidiCommon.h>

#include "SchweineSystemMaster.h"

FlameCC::FlameCC()
   : SchweineSystem::Module()
   , midiOutput()
   , connectTrigger()
   , voltageToCcValue(0.0, 10.0, 0.0, 127.0)
   , connectionLight(lights)
   , inputList(inputs)
{
   setup();

   inputList.append({Panel::Row1_InA,
                     Panel::Row2_InA,
                     Panel::Row3_InA,
                     Panel::Row4_InA,
                     Panel::Row5_InA,
                     Panel::Row6_InA,
                     Panel::Row7_InA,
                     Panel::Row8_InA,
                     Panel::Row1_InB,
                     Panel::Row2_InB,
                     Panel::Row3_InB,
                     Panel::Row4_InB,
                     Panel::Row5_InB,
                     Panel::Row6_InB,
                     Panel::Row7_InB,
                     Panel::Row8_InB});

   connectionLight.assign(Panel::RGB_Connect);
   connectToMidiDevice();
}

FlameCC::~FlameCC()
{
}

void FlameCC::process(const ProcessArgs& args)
{
   if (connectTrigger.process(params[Panel::Connect].getValue() > 3.0))
      connectToMidiDevice();

   if (-1 == midiOutput.getDeviceId()) // not connected
      return;

   for (uint8_t index = 0; index < 16; index++)
   {
      const float voltage = inputList[index]->getVoltage();
      const uint8_t controllerValue = static_cast<uint8_t>(voltageToCcValue(voltage));

      midi::Message controllerMessage;
      controllerMessage.setSize(3);
      controllerMessage.bytes[0] = Midi::Event::ControlChange | (Midi::Device::FlameCC - 1);
      controllerMessage.bytes[1] = Midi::ControllerMessage::User01;
      controllerMessage.bytes[2] = controllerValue;
      midiOutput.sendMessage(controllerMessage);
   }
}

void FlameCC::connectToMidiDevice()
{
   midiOutput.reset();
   connectionLight.setColor(SchweineSystem::Color{255, 0, 0});

   static const std::string targetDeviceName = SchweineSystem::Common::midiInterfaceMap.at(Midi::Device::FlameCC);
   std::cout << targetDeviceName << std::endl;

   for (const int& deviceId : midiOutput.getDeviceIds())
   {
      const std::string deviceName = midiOutput.getDeviceName(deviceId);
      // std::cout << deviceName << std::endl;

      if (targetDeviceName == deviceName)
      {
         std::cout << "connected to " << deviceName << " @ " << deviceId << std::endl;
         midiOutput.setDeviceId(deviceId);
         connectionLight.setColor(SchweineSystem::Color{0, 255, 0});
         return;
      }
   }
}

FlameCCWidget::FlameCCWidget(FlameCC* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelFlameCC = SchweineSystem::Master::the()->addModule<FlameCC, FlameCCWidget>("FlameCC");

