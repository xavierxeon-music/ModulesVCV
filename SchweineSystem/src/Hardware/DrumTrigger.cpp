#include "DrumTrigger.h"

#include <Tools/Variable.h>

const DrumTrigger::DeviceMap DrumTrigger::deviceMap = {{DeviceId::Erika, Midi::Device::Channel::DrumTrigger},
                                                       {DeviceId::BitBox2, Midi::Device::Channel::BitBox},
                                                       {DeviceId::BitBoxMini, Midi::Device::Channel::BitBoxMicro}};
const DrumTrigger::DeviceOrder DrumTrigger::deviceOrder = {DeviceId::Erika, DeviceId::BitBox2, DeviceId::BitBoxMini};

DrumTrigger::DrumTrigger()
   : Svin::Module()
   , Svin::Midi::Output(false)
   , deviceButton(this, Panel::Device)
   , deviceLightList(this)
   , deviceId(DeviceId::Erika)
   , input(this, Panel::Input)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , flank{}
{
   setup();
   registerAsBusModule<Svin::Midi::Bus>();

   deviceLightList.append({Panel::RGB_Erika, Panel::RGB_BitBox2, Panel::RGB_BitBoxMini});

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToMidiDevice();
}


void DrumTrigger::process(const ProcessArgs& args)
{
   Svin::Midi::Bus busMessage = getBusData<Svin::Midi::Bus>(Side::Left);
   sendBusData<Svin::Midi::Bus>(Side::Right, busMessage);

   if (deviceButton.isTriggered())
   {
      Variable::Enum<DeviceId::Value> var(deviceId, deviceOrder, true);
      var.increment();

      close();
      connectToMidiDevice();
   }

   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (!connected())
      return;

   static const uint8_t midiBaseNote = Note::availableNotes.at(1).midiValue + 12;
   const Midi::Channel channel = deviceMap.at(deviceId);

   const uint8_t maxIndex = input.getNumberOfChannels();
   for (uint8_t index = 0; index < maxIndex; index++)
   {
      const bool on = input.isOn(index);
      const Flank::State state = flank[index].observe(on);

      if (Flank::State::Rising == state)
         sendNoteOn(channel, midiBaseNote + index, 127);
      else if (Flank::State::Falling == state)
         sendNoteOff(channel, midiBaseNote + index);
   }

   for (uint8_t channel = 0; channel < busMessage.noOfChannels; channel++)
   {
      if (!busMessage.channels[channel].hasEvents)
         continue;

      const ::Midi::MessageList& messageList = busMessage.channels[channel].messageList;
      for (const Bytes& message : messageList)
         sendMessage(message);
   }
}

void DrumTrigger::updateDisplays()
{
   for (const DeviceId::Value& id : deviceOrder)
   {
      deviceLightList[id]->setActive(id == deviceId);
   }
}

void DrumTrigger::connectToMidiDevice()
{
   if (connected())
   {
      connectionButton.setOn();
      return;
   }

   connectionButton.setOff();

   const Midi::Device::Channel deviceChannel = deviceMap.at(deviceId);
   const std::string targetDeviceName = Svin::Midi::Common::interfaceMap.at(deviceChannel);

   setTargetDeviceName(targetDeviceName);

   if (!open())
      return;

   connectionButton.setOn();
}

void DrumTrigger::load(const Svin::Json::Object& rootObject)
{
   deviceId = static_cast<DeviceId::Value>(rootObject.get("deviceId").toInt());

   close();
   connectToMidiDevice();
}

void DrumTrigger::save(Svin::Json::Object& rootObject)
{
   rootObject.set("deviceId", static_cast<uint8_t>(deviceId));
}

// widget

DrumTriggerWidget::DrumTriggerWidget(DrumTrigger* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelDrumTrigger = Svin::Origin::the()->addModule<DrumTrigger, DrumTriggerWidget>("DrumTrigger");
