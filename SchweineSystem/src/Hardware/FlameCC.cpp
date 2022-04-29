#include "FlameCC.h"
#include "FlameCCPanel.h"

#include <Midi/MidiCommon.h>

#include "SchweineSystemMaster.h"

FlameCC::FlameCC()
   : SchweineSystem::Module()
   , SchweineSystem::MidiOutput(Midi::Device::FlameCC)
   , connectTrigger()
   , voltageToCcValue(0.0, 5.0, 0.0, 127.0)
   , connectionLight(lights)
   , inputList(inputs)
   , controllerValueStore{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
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

   if (!connected())
      return;

   for (uint8_t index = 0; index < 16; index++)
   {
      const float voltage = inputList[index]->getVoltage();
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
   connectionLight.setColor(SchweineSystem::Color{255, 0, 0});

   if (!open())
      return;

   connectionLight.setColor(SchweineSystem::Color{0, 255, 0});

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
   sysExMessage[1] = 0x7D;                                      // Header Flame module
   sysExMessage[2] = 0x0B;                                      // Flame module “μ16MCC”
   sysExMessage[3] = 0x01;                                      // version 1
   sysExMessage[4] = 0x06;                                      // data type 1 (dump all data)

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

FlameCCWidget::FlameCCWidget(FlameCC* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelFlameCC = SchweineSystem::Master::the()->addModule<FlameCC, FlameCCWidget>("FlameCC");

