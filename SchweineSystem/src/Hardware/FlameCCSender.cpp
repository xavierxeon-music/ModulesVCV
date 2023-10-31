#include "FlameCCSender.h"

#include <SvinOrigin.h>

FlameCCSender::FlameCCSender()
   : Svin::Module()
   , Svin::MidiOutput(Midi::Device::FlameCC)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , voltageToCcValue(0.0, 5.0, 0.0, 127.0)
   , input(this, Panel::Voltages)
   , valueStore{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
   , fullVoltSwitch(this, Panel::Half)
{
   setup();

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToMidiDevice();
}

void FlameCCSender::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (!connected())
      return;

   for (uint8_t index = 0; index < 16; index++)
   {
      float voltage = input.getVoltage(index);
      if (fullVoltSwitch.isOff())
         voltage *= 0.5;

      const uint8_t controllerValue = static_cast<uint8_t>(voltageToCcValue(voltage));
      if (controllerValue != valueStore[index])
      {
         const Midi::ControllerMessage message = static_cast<Midi::ControllerMessage>(Midi::ControllerMessage::User01 + index);
         sendControllerChange(Midi::Device::FlameCC, message, controllerValue);
         valueStore[index] = controllerValue;
      }
   }
}

void FlameCCSender::connectToMidiDevice()
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
      const uint8_t midiNote = 41 + output; // note F2
      sendNoteOn(Midi::Device::FlameCC, midiNote, 127);
   }
}

void FlameCCSender::sendSysEx()
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

void FlameCCSender::load(const Svin::Json::Object& rootObject)
{
   const bool on = rootObject.get("fullVoltage").toBool();
   fullVoltSwitch.setState(on);
}

void FlameCCSender::save(Svin::Json::Object& rootObject)
{
   const bool on = fullVoltSwitch.isOn();
   rootObject.set("fullVoltage", on);
}

// widget

FlameCCSenderWidget::FlameCCSenderWidget(FlameCCSender* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// create module
Model* modelFlameCCSender = Svin::Origin::the()->addModule<FlameCCSender, FlameCCSenderWidget>("FlameCCSender");
