#include "FlameCC.h"
#include "FlameCCPanel.h"

#include <Midi/MidiCommon.h>

#include <SyJson.h>
#include <SyMaster.h>

FlameCC::FlameCC()
   : Sy::Module()
   , Sy::MidiOutput(Midi::Device::FlameCC)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , voltageToCcValue(0.0, 5.0, 0.0, 127.0)
   , inputList(inputs)
   , controllerValueStore{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
   , fullVoltSwitchList(this)
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

   fullVoltSwitchList.append({Panel::Row1_HalfA,
                              Panel::Row2_HalfA,
                              Panel::Row3_HalfA,
                              Panel::Row4_HalfA,
                              Panel::Row5_HalfA,
                              Panel::Row6_HalfA,
                              Panel::Row7_HalfA,
                              Panel::Row8_HalfA,
                              Panel::Row1_HalfB,
                              Panel::Row2_HalfB,
                              Panel::Row3_HalfB,
                              Panel::Row4_HalfB,
                              Panel::Row5_HalfB,
                              Panel::Row6_HalfB,
                              Panel::Row7_HalfB,
                              Panel::Row8_HalfB});

   connectionButton.setDefaultColor(Sy::Color{0, 255, 0});
   connectToMidiDevice();
}

void FlameCC::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (!connected())
      return;

   for (uint8_t index = 0; index < 16; index++)
   {
      float voltage = inputList[index]->getVoltage();
      if (fullVoltSwitchList[index]->isOff())
         voltage *= 0.5;

      const uint8_t controllerValue = static_cast<uint8_t>(voltageToCcValue(voltage));
      if (controllerValue != controllerValueStore[index])
      {
         const Midi::ControllerMessage message = static_cast<Midi::ControllerMessage>(Midi::ControllerMessage::User01 + index);
         sendControllerChange(Midi::Device::FlameCC, message, controllerValue);
         controllerValueStore[index] = controllerValue;
      }
   }
}

void FlameCC::connectToMidiDevice()
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

   //sendSysEx();

   for (uint8_t output = 0; output < 16; output++)
   {
      const Note note = Note::fromMidi(41 + output); // note F2
      sendNoteOn(Midi::Device::FlameCC, note, 127);
   }
}

void FlameCC::sendSysEx()
{
   std::vector<uint8_t> sysExMessage(38);

   sysExMessage[0] = static_cast<uint8_t>(Midi::Event::System); // Exclusive Status
   sysExMessage[1] = Midi::Manufacturer::EducationalUse;        // Header Flame module
   sysExMessage[2] = 0x0B;                                      // Flame module “μ16MCC”
   sysExMessage[3] = 0x01;                                      // version 1

   sysExMessage[4] = 0x06; // data type 1 (dump all data)

   for (uint8_t index = 0; index < 16; index++)
   {
      // MIDI channels for CV 16 outputs (range: 00=channel 1 .. 0F=channel 16)
      sysExMessage[5 + index] = (Midi::Device::FlameCC - 1);

      // control change numbers for 15 outputs
      const uint8_t message = static_cast<uint8_t>(Midi::ControllerMessage::User01) + index;
      sysExMessage[21 + index] = message;
   }

   sysExMessage[37] = static_cast<uint8_t>(Midi::Event::SysExEnd); // End of Exclusive
   sendMessage(sysExMessage);
}

void FlameCC::load(const Sy::Json::Object& rootObject)
{
   Sy::Json::Array fullVoltageArray = rootObject.get("fullVoltage").toArray();
   for (uint8_t index = 0; index < 16; index++)
   {
      const bool on = fullVoltageArray.get(index).toBool();
      fullVoltSwitchList[index]->setState(on);
   }
}

void FlameCC::save(Sy::Json::Object& rootObject)
{
   Sy::Json::Array fullVoltageArray;
   for (uint8_t index = 0; index < 16; index++)
   {
      const bool on = fullVoltSwitchList[index]->isOn();
      fullVoltageArray.append(on);
   }

   rootObject.set("fullVoltage", fullVoltageArray);
}

// widget

FlameCCWidget::FlameCCWidget(FlameCC* module)
   : Sy::ModuleWidget(module)
{
   setup();
}

Model* modelFlameCC = Sy::Master::the()->addModule<FlameCC, FlameCCWidget>("FlameCC");
