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

Svin::MidiCommon::MidiCommon(bool isVirtual)
   : isVirtual(isVirtual)
   , virtualOpen(false)
   , targetDeviceName()
{
}

void Svin::MidiCommon::midiError(RtMidiError::Type type, const std::string& errorText, void* userData)
{
   (void)userData;

   std::cout << "MIDI ERROR: " << type << ",  " << errorText << std::endl;
}

void Svin::MidiCommon::setTargetDeviceName(const std::string& newTargetDeviceName)
{
   targetDeviceName = newTargetDeviceName;
}

// output

Svin::MidiOutput::MidiOutput(bool isVirtual)
   : MidiCommon(isVirtual)
   , midiOutput()
{
   midiOutput.setErrorCallback(&MidiCommon::midiError);
}

Svin::MidiOutput::MidiOutput(const std::string& targetDeviceName, bool isVirtual)
   : MidiOutput(isVirtual)
{
   setTargetDeviceName(targetDeviceName);
   open();
}

Svin::MidiOutput::MidiOutput(const Midi::Device::Channel& deviceChannel)
   : MidiOutput(MidiCommon::interfaceMap.at(deviceChannel), false)
{
}

Svin::MidiOutput::~MidiOutput()
{
   close();
}

bool Svin::MidiOutput::open(bool verbose)
{
   if (!isVirtual)
   {
      for (unsigned int port = 0; port < midiOutput.getPortCount(); port++)
      {
         const std::string deviceName = midiOutput.getPortName(port);
         if (verbose)
            std::cout << deviceName << std::endl;

         if (targetDeviceName == deviceName)
         {
            std::cout << "connected to " << deviceName << " @ " << port << std::endl;
            midiOutput.openPort(port);
            return true;
         }
      }

      return false;
   }

   midiOutput.openVirtualPort(targetDeviceName);
   virtualOpen = true;
   return true;
}

void Svin::MidiOutput::close()
{
   if (!isVirtual && !midiOutput.isPortOpen())
      return;

   midiOutput.closePort();
   virtualOpen = false;
}

bool Svin::MidiOutput::connected()
{
   if (isVirtual)
      return virtualOpen;

   return midiOutput.isPortOpen();
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

   midiOutput.sendMessage(message.data(), message.size());
}

// input

Svin::MidiInput::MidiInput(bool isVirtual)
   : MidiCommon(isVirtual)
   , Midi::Parser()
   , midiInput()
   , docBufferMap()
{
   midiInput.setErrorCallback(&MidiCommon::midiError);
   midiInput.setCallback(&MidiInput::midiReceive, this);
   midiInput.ignoreTypes(false, false, false); // do not ignore anything
}

Svin::MidiInput::MidiInput(const std::string& targetDeviceName, bool isVirtual)
   : MidiInput(isVirtual)
{
   setTargetDeviceName(targetDeviceName);
   open();
}

Svin::MidiInput::MidiInput(const Midi::Device::Channel& deviceChannel)
   : MidiInput(MidiCommon::interfaceMap.at(deviceChannel), false)
{
}

Svin::MidiInput::~MidiInput()
{
   close();
}

bool Svin::MidiInput::open(bool verbose)
{
   if (!isVirtual)
   {
      for (unsigned int port = 0; port < midiInput.getPortCount(); port++)
      {
         const std::string deviceName = midiInput.getPortName(port);
         if (verbose)
            std::cout << deviceName << std::endl;

         if (targetDeviceName == deviceName)
         {
            std::cout << "connected to " << deviceName << " @ " << port << std::endl;
            midiInput.openPort(port);
            return true;
         }
      }

      return false;
   }

   midiInput.openVirtualPort(targetDeviceName);

   virtualOpen = true;
   return true;
}

void Svin::MidiInput::close()
{
   if (!isVirtual && !midiInput.isPortOpen())
      return;

   midiInput.closePort();
   virtualOpen = false;
}

bool Svin::MidiInput::connected()
{
   if (isVirtual)
      return virtualOpen;

   return midiInput.isPortOpen();
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

void Svin::MidiInput::midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData)
{
   (void)timeStamp;

   if (!message)
      return;

   MidiInput* me = static_cast<MidiInput*>(userData);
   if (!me)
      return;

   static Bytes buffer;
   auto maybeProcessBuffer = [&]()
   {
      if (0 == buffer.size())
         return;

      me->processMessage(buffer);
      buffer.clear();
   };

   static const uint8_t mask = 0x80;
   for (const uint8_t byte : *message)
   {
      const uint8_t test = byte & mask;
      if (test == mask) // new message start
         maybeProcessBuffer();

      buffer.push_back(byte);
   }
   maybeProcessBuffer();
}
