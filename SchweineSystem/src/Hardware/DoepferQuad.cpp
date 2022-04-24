#include "DoepferQuad.h"
#include "DoepferQuadPanel.h"

#include <SchweineSystemMaster.h>

DoepferQuad::DoepferQuad()
   : SchweineSystem::Module()
   , SchweineSystem::MidiOutput(Midi::Device::DopeferQuad1)
   , connectTrigger()
   , voltageToNote(0.0, 10.0, 24.0, 127.0)
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

   if (!connected())
      return;

   for (ChannelStore::Map::iterator it = channelMap.begin(); it != channelMap.end(); it++)
   {
      const Midi::Channel& midiChannel = it->first;
      ChannelStore& channelStore = it->second;

      if (channelStore.requestSendNote)
      {
         channelStore.requestSendNote = false;
         sendNoteOn(midiChannel, Note::fromMidi(channelStore.note), channelStore.velocity);
      }
      else
      {
         const float noteVoltage = inputs[channelStore.inputIdList[0]].getVoltage();
         uint8_t note = static_cast<uint8_t>(voltageToNote(noteVoltage));

         const float velocityVoltage = inputs[channelStore.inputIdList[1]].getVoltage();
         const bool velocityConnected = inputs[channelStore.inputIdList[1]].isConnected();
         uint8_t velocity = velocityConnected ? static_cast<uint8_t>(voltageToCcValue(velocityVoltage)) : 64;

         if (note != channelStore.note || velocity != channelStore.velocity)
         {
            sendNoteOff(midiChannel, Note::fromMidi(channelStore.note));
            channelStore.requestSendNote = true;
            channelStore.note = note;
            channelStore.velocity = velocity;
         }
      }

      const float controllerVoltage = inputs[channelStore.inputIdList[2]].getVoltage();
      uint8_t controllerValue = static_cast<uint8_t>(voltageToCcValue(controllerVoltage));

      if (controllerValue != channelStore.controllerValue)
      {
         sendControllerChange(midiChannel, Midi::ControllerMessage::User01, controllerValue);
         channelStore.controllerValue = controllerValue;
      }
   }
}

void DoepferQuad::connectToMidiDevice()
{
   connectionLight.setColor(SchweineSystem::Color{255, 0, 0});

   if (!open())
      return;

   connectionLight.setColor(SchweineSystem::Color{0, 255, 0});
   for (ChannelStore::Map::iterator it = channelMap.begin(); it != channelMap.end(); it++)
   {
      const Midi::Channel midiChannel = it->first;
      sendControllerChange(midiChannel, Midi::ControllerMessage::AllNotesOff, 0);
   }
}

DoepferQuadWidget::DoepferQuadWidget(DoepferQuad* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelDoepferQuad = SchweineSystem::Master::the()->addModule<DoepferQuad, DoepferQuadWidget>("DoepferQuad");

