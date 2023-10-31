#include "SvinMidi.h"

#include <Tools/SevenBit.h>

// common

const Svin::MidiCommon::InterfaceMap Svin::MidiCommon::interfaceMap = {
   {Midi::Device::Splitter, "SWITCH"},
   {Midi::Device::DopeferQuad1, "DoepferQuad"},
   {Midi::Device::DopeferQuad2, "DoepferQuad"},
   {Midi::Device::DopeferQuad3, "DoepferQuad"},
   {Midi::Device::DopeferQuad4, "DoepferQuad"},
   {Midi::Device::KeyStep1, "KeyStep Pro"},
   {Midi::Device::KeyStep2, "KeyStep Pro"},
   {Midi::Device::KeyStep3, "KeyStep Pro"},
   {Midi::Device::KeyStep4, "KeyStep Pro"},
   {Midi::Device::Daisy, "SWITCH"},
   {Midi::Device::DrumTrigger, "DrumTrigger"},
   {Midi::Device::VCMC, "ESI M4U eX Port 6"},
   {Midi::Device::ACDC, "OWL-ACDC"},
   {Midi::Device::Metropolix, "Metropolix"},
   {Midi::Device::FlameCC, "FlameCC"},
   {Midi::Device::BitBox, "SWITCH"},
   {Midi::Device::BitBoxMicro, "SWITCH"},
   {Midi::Device::ToNerdSEQ, "ESI M4U eX Port 7"},
   {Midi::Device::FromNerdSEQ, "ESI M4U eX Port 3"},
};

Svin::MidiCommon::MidiCommon()
   : targetDeviceName()
{
}

void Svin::MidiCommon::setTargetDeviceName(const std::string& newTargetDeviceName)
{
   targetDeviceName = newTargetDeviceName;
}

int Svin::MidiCommon::findDeviceId(rack::midi::Port* port, bool verbose) const
{
   for (int id : port->getDeviceIds())
   {
      const std::string deviceName = port->getDeviceName(id);
      if (verbose)
         std::cout << id << " " << deviceName << std::endl;

      if (targetDeviceName == deviceName)
         return id;
   }

   return -1;
}

// output

Svin::MidiOutput::MidiOutput()
   : MidiCommon()
   , rack::midi::Output()
{
}

Svin::MidiOutput::MidiOutput(const std::string& targetDeviceName)
   : MidiOutput()
{
   setTargetDeviceName(targetDeviceName);
   open();
}

Svin::MidiOutput::MidiOutput(const Midi::Device::Channel& deviceChannel)
   : MidiOutput(MidiCommon::interfaceMap.at(deviceChannel))
{
}

Svin::MidiOutput::~MidiOutput()
{
   close();
}

bool Svin::MidiOutput::open(bool verbose)
{
   const int id = findDeviceId(this, verbose);
   if (id < 0)
      return false;

   setDeviceId(id);
   return true;
}

void Svin::MidiOutput::close()
{
   setDeviceId(-1);
}

bool Svin::MidiOutput::connected()
{
   return (-1 == getDeviceId());
}

void Svin::MidiOutput::sendNoteOn(const Midi::Channel& channel, const uint8_t& midiNote, const Midi::Velocity& velocity)
{
   if (0 == channel || channel > 16)
   {
      std::cerr << "invalid midi channel" << std::endl;
      return;
   }

   std::vector<unsigned char> onMessage(3);
   onMessage[0] = (Midi::Event::NoteOn | (channel - 1));
   onMessage[1] = midiNote;
   onMessage[2] = velocity;
   sendMessage(onMessage);
}

void Svin::MidiOutput::sendNoteOff(const Midi::Channel& channel, const uint8_t& midiNote)
{
   if (0 == channel || channel > 16)
   {
      std::cerr << "invalid midi channel" << std::endl;
      return;
   }

   std::vector<unsigned char> offMessage(3);
   offMessage[0] = (Midi::Event::NoteOff | (channel - 1));
   offMessage[1] = midiNote;
   offMessage[2] = 64;
   sendMessage(offMessage);
}

void Svin::MidiOutput::sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
   if (0 == channel || channel > 16)
   {
      std::cerr << "invalid midi channel" << std::endl;
      return;
   }

   std::vector<unsigned char> ccMessage(3);
   ccMessage[0] = (Midi::Event::ControlChange | (channel - 1));
   ccMessage[1] = controllerMessage;
   ccMessage[2] = value;
   sendMessage(ccMessage);
}

void Svin::MidiOutput::sendDocument(const Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex)
{
   sendControllerChange(channel, Midi::ControllerMessage::DataInit, docIndex);

   const Bytes content = object.toBytes();
   const std::string data = SevenBit::encode(content);
   for (const char& byte : data)
      sendControllerChange(channel, Midi::ControllerMessage::DataBlock, byte);

   sendControllerChange(channel, Midi::ControllerMessage::DataApply, docIndex);
}

void Svin::MidiOutput::sendMessage(const Bytes& message)
{
   if (!connected())
      return;

   rack::midi::Message internal;
   internal.bytes = message;

   rack::midi::Output::sendMessage(internal);
}

// input

Svin::MidiInput::MidiInput()
   : MidiCommon()
   , Midi::Parser()
   , rack::midi::Input()
   , docBufferMap()
{
}

Svin::MidiInput::MidiInput(const std::string& targetDeviceNamel)
   : MidiInput()
{
   setTargetDeviceName(targetDeviceName);
   open();
}

Svin::MidiInput::MidiInput(const Midi::Device::Channel& deviceChannel)
   : MidiInput(MidiCommon::interfaceMap.at(deviceChannel))
{
}

Svin::MidiInput::~MidiInput()
{
   close();
}

bool Svin::MidiInput::open(bool verbose)
{
   const int id = findDeviceId(this, verbose);
   if (id < 0)
      return false;

   setDeviceId(id);
   return true;
}

void Svin::MidiInput::close()
{
   setDeviceId(-1);
}

bool Svin::MidiInput::connected()
{
   return (-1 == getDeviceId());
}

void Svin::MidiInput::controllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
   Midi::Parser::controllerChange(channel, controllerMessage, value);

   if (controllerMessage == Midi::ControllerMessage::DataInit)
   {
      docBufferMap[channel].clear();
   }
   else if (controllerMessage == Midi::ControllerMessage::DataBlock)
   {
      docBufferMap[channel].push_back(value);
   }
   else if (controllerMessage == Midi::ControllerMessage::DataApply)
   {
      const Bytes content = SevenBit::decode(docBufferMap[channel]);
      const Json::Object doc(content);
      document(channel, doc, value);
   }
}

void Svin::MidiInput::document(const Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex)
{
   (void)channel;
   (void)object;
   (void)docIndex;
   // do nothing
}

void Svin::MidiInput::onMessage(const rack::midi::Message& message)
{
}
