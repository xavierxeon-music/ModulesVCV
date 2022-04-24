#include "DoepferQuad.h"
#include "DoepferQuadPanel.h"

#include <SchweineSystemMaster.h>

DoepferQuad::DoepferQuad()
   : SchweineSystem::Module()
   , midiOutput()
   , connectTrigger()
   , voltageToCcValue(0.0, 10.0, 0.0, 127.0)
   , connectionLight(lights)
   , channelMap()
{
   setup();

   connectionLight.assign(Panel::RGB_Connect);
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

   if (!midiOutput.isPortOpen()) // not connected
      return;

   for (ChannelStore::Map::iterator it = channelMap.begin(); it != channelMap.end(); it++)
   {
      const Midi::Channel& midiChannel = it->first;
      ChannelStore& channelStore = it->second;

      if (1 < channelStore.sendNote)
      {
         channelStore.sendNote--;
      }
      else if (1 == channelStore.sendNote)
      {
         channelStore.sendNote = 0;

         std::vector<unsigned char> onMessage(3);
         onMessage[0] = (Midi::Event::NoteOn | (midiChannel - 1));
         onMessage[1] = channelStore.note;
         onMessage[2] = channelStore.velocity;
         midiOutput.sendMessage(&onMessage);
      }
      else
      {
         const float noteVoltage = inputs[channelStore.inputIdList[0]].getVoltage();
         uint8_t note = static_cast<uint8_t>(voltageToCcValue(noteVoltage)) + 24;

         const float velocityVoltage = inputs[channelStore.inputIdList[1]].getVoltage();
         const bool velocityConnected = inputs[channelStore.inputIdList[1]].isConnected();
         uint8_t velocity = velocityConnected ? static_cast<uint8_t>(voltageToCcValue(velocityVoltage)) : 127;

         if (note != channelStore.note || velocity != channelStore.velocity)
         {
            std::vector<unsigned char> offMessage(3);
            offMessage[0] = (Midi::Event::NoteOff | (midiChannel - 1));
            offMessage[1] = channelStore.note;
            offMessage[2] = 64;
            midiOutput.sendMessage(&offMessage);

            channelStore.sendNote = 200;
            channelStore.note = note;
            channelStore.velocity = velocity;
         }
      }

      const float controllerVoltage = inputs[channelStore.inputIdList[2]].getVoltage();
      uint8_t controllerValue = static_cast<uint8_t>(voltageToCcValue(controllerVoltage));

      if (controllerValue != channelStore.controllerValue)
      {
         std::vector<unsigned char> controllerMessage(3);
         controllerMessage[0] = (Midi::Event::ControlChange | (midiChannel - 1));
         controllerMessage[1] = Midi::ControllerMessage::User01;
         controllerMessage[2] = controllerValue;
         midiOutput.sendMessage(&controllerMessage);

         channelStore.controllerValue = controllerValue;
      }
   }
}

void DoepferQuad::connectToMidiDevice()
{
   connectionLight.setColor(SchweineSystem::Color{255, 0, 0});

   static const std::string targetDeviceName = SchweineSystem::Common::midiInterfaceMap.at(Midi::Device::DopeferQuad1);
   std::cout << targetDeviceName << std::endl;

   auto sendAllNotesOff = [&]()
   {
      for (ChannelStore::Map::iterator it = channelMap.begin(); it != channelMap.end(); it++)
      {
         const Midi::Channel midiChannel = (it->first - 1);

         std::vector<unsigned char> message(3);
         message[0] = Midi::Event::ControlChange & midiChannel;
         message[1] = Midi::ControllerMessage::AllNotesOff;
         message[2] = 0;
         midiOutput.sendMessage(&message);
      }
   };

   for (unsigned int port = 0; port < midiOutput.getPortCount(); port++)
   {
      const std::string deviceName = midiOutput.getPortName(port);
      //std::cout << deviceName << std::endl;

      if (targetDeviceName == deviceName)
      {
         std::cout << "connected to " << deviceName << " @ " << port << std::endl;
         midiOutput.openPort(port);
         connectionLight.setColor(SchweineSystem::Color{0, 255, 0});
         sendAllNotesOff();
         return;
      }
   }
}

DoepferQuadWidget::DoepferQuadWidget(DoepferQuad* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelDoepferQuad = SchweineSystem::Master::the()->addModule<DoepferQuad, DoepferQuadWidget>("DoepferQuad");

