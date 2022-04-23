#include "DoepferQuad.h"
#include "DoepferQuadPanel.h"

#include <SchweineSystemMaster.h>

DoepferQuad::DoepferQuad()
   : Module()
   , midiOutput()
   , connectTrigger()
   , voltageToCcValue(0.0, 10.0, 0.0, 127.0)
   , connectionLight(lights)
   , channelMap()
{
   setup();

   connectionLight.assign(Panel::Red_Connect);
   connectToMidiDevice();

   channelMap[Midi::Device::DopeferQuad1].inputIdList = {Panel::Channel1_In1, Panel::Channel1_In2, Panel::Channel1_In3};
   channelMap[Midi::Device::DopeferQuad2].inputIdList = {Panel::Channel2_In1, Panel::Channel2_In2, Panel::Channel2_In3};
   channelMap[Midi::Device::DopeferQuad3].inputIdList = {Panel::Channel3_In1, Panel::Channel3_In2, Panel::Channel3_In3};
   channelMap[Midi::Device::DopeferQuad4].inputIdList = {Panel::Channel4_In1, Panel::Channel4_In2, Panel::Channel4_In3};
}

DoepferQuad::~DoepferQuad()
{
}

void DoepferQuad::process(const ProcessArgs& args)
{
   if (connectTrigger.process(params[Panel::Connect].getValue() > 3.0))
      connectToMidiDevice();

   if (-1 == midiOutput.getDeviceId()) // not connected
      return;

   for (ChannelStore::Map::iterator it = channelMap.begin(); it != channelMap.end(); it++)
   {
      const Midi::Channel& midiChannel = it->first;
      ChannelStore& channelStore = it->second;

      const float noteVoltage = inputs[channelStore.inputIdList[0]].getVoltage();
      uint8_t note = static_cast<uint8_t>(voltageToCcValue(noteVoltage));

      const float velocityVoltage = inputs[channelStore.inputIdList[1]].getVoltage();
      const bool velocityConnected = inputs[channelStore.inputIdList[1]].isConnected();
      uint8_t velocity = velocityConnected ? static_cast<uint8_t>(voltageToCcValue(velocityVoltage)) : 127;

      if (note != channelStore.prevNote || velocity != channelStore.prevVelocity)
      {
         midi::Message offMessage;
         offMessage.setSize(3);
         offMessage.bytes[0] = Midi::Event::NoteOff | (midiChannel - 1);
         offMessage.bytes[1] = channelStore.prevNote;
         offMessage.bytes[2] = 0;
         midiOutput.sendMessage(offMessage);

         midi::Message onMessage;
         onMessage.setSize(3);
         onMessage.bytes[0] = Midi::Event::NoteOn | (midiChannel - 1);
         onMessage.bytes[1] = note;
         onMessage.bytes[2] = velocity;
         midiOutput.sendMessage(onMessage);

         channelStore.prevNote = note;
         channelStore.prevVelocity = velocity;
      }

      const float controllerVoltage = inputs[channelStore.inputIdList[2]].getVoltage();
      uint8_t controllerValue = static_cast<uint8_t>(voltageToCcValue(controllerVoltage));

      if (controllerValue != channelStore.prevControllerValue)
      {
         midi::Message controllerMessage;
         controllerMessage.setSize(3);
         controllerMessage.bytes[0] = Midi::Event::ControlChange | (midiChannel - 1);
         controllerMessage.bytes[1] = Midi::ControllerMessage::User01;
         controllerMessage.bytes[2] = controllerValue;
         midiOutput.sendMessage(controllerMessage);

         channelStore.prevControllerValue = controllerValue;
      }
   }
}

void DoepferQuad::connectToMidiDevice()
{
   midiOutput.reset();
   connectionLight.setColor(SchweineSystem::Color{255, 0, 0});

   static const std::string targetDeviceName = SchweineSystem::Common::midiInterfaceMap.at(Midi::Device::DopeferQuad1);
   std::cout << targetDeviceName << std::endl;

   auto sendAllNotesOff = [&]()
   {
      for (ChannelStore::Map::iterator it = channelMap.begin(); it != channelMap.end(); it++)
      {
         const Midi::Channel midiChannel = (it->first - 1);

         midi::Message message;
         message.bytes[0] = Midi::Event::ControlChange & midiChannel;
         message.bytes[1] = Midi::ControllerMessage::AllNotesOff;
         message.bytes[2] = 0;
         midiOutput.sendMessage(message);
      }
   };

   for (const int& deviceId : midiOutput.getDeviceIds())
   {
      const std::string deviceName = midiOutput.getDeviceName(deviceId);
      // std::cout << deviceName << std::endl;

      if (targetDeviceName == deviceName)
      {
         std::cout << "connected to " << deviceName << " @ " << deviceId << std::endl;
         midiOutput.setDeviceId(deviceId);
         connectionLight.setColor(SchweineSystem::Color{0, 255, 0});
         sendAllNotesOff();
         return;
      }
   }
}

DoepferQuadWidget::DoepferQuadWidget(DoepferQuad* module)
: ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;
}

Model* modelDoepferQuad = SchweineSystem::Master::the()->addModule<DoepferQuad, DoepferQuadWidget>("DoepferQuad");

