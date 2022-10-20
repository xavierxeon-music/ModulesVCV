#include "SvinMidi.h"

#include <Tools/SevenBit.h>

// common

const Svin::Midi::Common::InterfaceMap Svin::Midi::Common::interfaceMap = {
   {::Midi::Device::Splitter, "ESI M4U eX Port 4"},
   {::Midi::Device::DopeferQuad1, "ESI M4U eX Port 1"},
   {::Midi::Device::DopeferQuad2, "ESI M4U eX Port 1"},
   {::Midi::Device::DopeferQuad3, "ESI M4U eX Port 1"},
   {::Midi::Device::DopeferQuad4, "ESI M4U eX Port 1"},
   {::Midi::Device::KeyStep1, "ESI M4U eX Port 5"},
   {::Midi::Device::KeyStep2, "ESI M4U eX Port 5"},
   {::Midi::Device::KeyStep3, "ESI M4U eX Port 5"},
   {::Midi::Device::KeyStep4, "ESI M4U eX Port 5"},
   {::Midi::Device::Daisy, "ESI M4U eX Port 4"},
   {::Midi::Device::DrumTrigger, "ESI M4U eX Port 8"},
   {::Midi::Device::VCMC, "ESI M4U eX Port 6"},
   {::Midi::Device::ACDC, "OWL-ACDC"},
   {::Midi::Device::Metropolix, "Metropolix"},
   {::Midi::Device::FlameCC, "ESI M4U eX Port 4"},
   {::Midi::Device::BitBox, "ESI M4U eX Port 4"},
   {::Midi::Device::BitBoxMicro, "ESI M4U eX Port 4"},
   {::Midi::Device::NerdSEQ, "ESI M4U eX Port 7"},
};

Svin::Midi::Common::Common(bool isVirtual)
   : isVirtual(isVirtual)
   , virtualOpen(false)
   , targetDeviceName()
{
}

void Svin::Midi::Common::midiError(RtMidiError::Type type, const std::string& errorText, void* userData)
{
   (void)userData;

   std::cout << "MIDI ERROR: " << type << ",  " << errorText << std::endl;
}

void Svin::Midi::Common::setTargetDeviceName(const std::string& newTargetDeviceName)
{
   targetDeviceName = newTargetDeviceName;
}

// output

Svin::Midi::Output::Output(bool isVirtual)
   : Common(isVirtual)
   , midiOutput()
{
   midiOutput.setErrorCallback(&Common::midiError);
}

Svin::Midi::Output::Output(const std::string& targetDeviceName, bool isVirtual)
   : Output(isVirtual)
{
   setTargetDeviceName(targetDeviceName);
   open();
}

Svin::Midi::Output::Output(const ::Midi::Device::Channel& deviceChannel)
   : Output(Common::interfaceMap.at(deviceChannel), false)
{
}

Svin::Midi::Output::~Output()
{
   close();
}

bool Svin::Midi::Output::open(bool verbose)
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

void Svin::Midi::Output::close()
{
   if (!isVirtual && !midiOutput.isPortOpen())
      return;

   midiOutput.closePort();
   virtualOpen = false;
}

bool Svin::Midi::Output::connected()
{
   if (isVirtual)
      return virtualOpen;

   return midiOutput.isPortOpen();
}

void Svin::Midi::Output::sendNoteOn(const ::Midi::Channel& channel, const uint8_t& midiNote, const ::Midi::Velocity& velocity)
{
   if (0 == channel || channel > 16)
   {
      std::cerr << "invalid midi channel" << std::endl;
      return;
   }

   std::vector<unsigned char> onMessage(3);
   onMessage[0] = (::Midi::Event::NoteOn | (channel - 1));
   onMessage[1] = midiNote;
   onMessage[2] = velocity;
   sendMessage(onMessage);
}

void Svin::Midi::Output::sendNoteOff(const ::Midi::Channel& channel, const uint8_t& midiNote)
{
   if (0 == channel || channel > 16)
   {
      std::cerr << "invalid midi channel" << std::endl;
      return;
   }

   std::vector<unsigned char> offMessage(3);
   offMessage[0] = (::Midi::Event::NoteOff | (channel - 1));
   offMessage[1] = midiNote;
   offMessage[2] = 64;
   sendMessage(offMessage);
}

void Svin::Midi::Output::sendControllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
   if (0 == channel || channel > 16)
   {
      std::cerr << "invalid midi channel" << std::endl;
      return;
   }

   std::vector<unsigned char> ccMessage(3);
   ccMessage[0] = (::Midi::Event::ControlChange | (channel - 1));
   ccMessage[1] = controllerMessage;
   ccMessage[2] = value;
   sendMessage(ccMessage);
}

void Svin::Midi::Output::sendDocument(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex)
{
   sendControllerChange(channel, ::Midi::ControllerMessage::DataInit, docIndex);

   const Bytes content = object.toBytes();
   const std::string data = SevenBit::encode(content);
   for (const char& byte : data)
      sendControllerChange(channel, ::Midi::ControllerMessage::DataBlock, byte);

   sendControllerChange(channel, ::Midi::ControllerMessage::DataApply, docIndex);
}

void Svin::Midi::Output::sendMessage(const std::vector<uint8_t>& message)
{
   if (!connected())
      return;

   midiOutput.sendMessage(message.data(), message.size());
}

// input

Svin::Midi::Input::Input(bool isVirtual)
   : Common(isVirtual)
   , midiInput()
   , docBufferMap()
{
   midiInput.setErrorCallback(&Common::midiError);
   midiInput.setCallback(&Input::midiReceive, this);
   midiInput.ignoreTypes(false, false, false); // do not ignore anything
}

Svin::Midi::Input::Input(const std::string& targetDeviceName, bool isVirtual)
   : Input(isVirtual)
{
   setTargetDeviceName(targetDeviceName);
   open();
}

Svin::Midi::Input::Input(const ::Midi::Device::Channel& deviceChannel)
   : Input(Common::interfaceMap.at(deviceChannel), false)
{
}

Svin::Midi::Input::~Input()
{
   close();
}

bool Svin::Midi::Input::open(bool verbose)
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

void Svin::Midi::Input::close()
{
   if (!isVirtual && !midiInput.isPortOpen())
      return;

   midiInput.closePort();
   virtualOpen = false;
}

bool Svin::Midi::Input::connected()
{
   if (isVirtual)
      return virtualOpen;

   return midiInput.isPortOpen();
}

void Svin::Midi::Input::clockTick()
{
   // do nothing
}

void Svin::Midi::Input::songPosition(const uint16_t position)
{
   (void)position;
   // do nothing
}

void Svin::Midi::Input::noteOn(const ::Midi::Channel& channel, const uint8_t& midiNote, const ::Midi::Velocity& velocity)
{
   (void)channel;
   (void)midiNote;
   (void)velocity;
   // do nothing
}

void Svin::Midi::Input::noteOff(const ::Midi::Channel& channel, const uint8_t& midiNote)
{
   (void)channel;
   (void)midiNote;
   // do nothing
}

void Svin::Midi::Input::controllerChange(const ::Midi::Channel& channel, const ::Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
   if (controllerMessage == ::Midi::ControllerMessage::DataInit)
   {
      docBufferMap[channel].clear();
   }
   else if (controllerMessage == ::Midi::ControllerMessage::DataBlock)
   {
      docBufferMap[channel].push_back(value);
   }
   else if (controllerMessage == ::Midi::ControllerMessage::DataApply)
   {
      const Bytes content = SevenBit::decode(docBufferMap[channel]);
      const Json::Object doc(content);
      document(channel, doc, value);
   }
}

void Svin::Midi::Input::document(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex)
{
   (void)channel;
   (void)object;
   (void)docIndex;
   // do nothing
}

void Svin::Midi::Input::midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData)
{
   (void)timeStamp;

   if (!message)
      return;

   Input* me = static_cast<Input*>(userData);
   if (!me)
      return;

   static Bytes buffer;
   auto maybeProcessBuffer = [&]()
   {
      if (0 == buffer.size())
         return;

      me->prcocess(buffer);
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

void Svin::Midi::Input::prcocess(const Bytes& buffer)
{
   const bool isSystemEvent = (0xF0 == (buffer[0] & 0xF0));
   if (isSystemEvent)
   {
      const ::Midi::Event event = static_cast<::Midi::Event>(buffer[0]);
      if (::Midi::Event::Clock == event)
      {
         clockTick();
      }
      else if (::Midi::Event::SongPositionPointer == event)
      {
         const uint8_t frontByte = buffer[1];
         const uint8_t backByte = buffer[2];
         const uint16_t position = frontByte * 128 + backByte;

         songPosition(position);
      }
   }
   else
   {
      const ::Midi::Event event = static_cast<::Midi::Event>(buffer[0] & 0xF0);
      const ::Midi::Channel channel = 1 + (buffer[0] & 0x0F);

      if (::Midi::Event::NoteOn == event)
      {
         const uint8_t midiNote = buffer[1];
         const ::Midi::Velocity velocity = buffer[2];

         noteOn(channel, midiNote, velocity);
      }
      else if (::Midi::Event::NoteOff == event)
      {
         const uint8_t midiNote = buffer[1];

         noteOff(channel, midiNote);
      }
      else if (::Midi::Event::ControlChange == event)
      {
         const ::Midi::ControllerMessage message = static_cast<::Midi::ControllerMessage>(buffer[1]);
         const uint8_t value = buffer[2];

         controllerChange(channel, message, value);
      }
   }
}
