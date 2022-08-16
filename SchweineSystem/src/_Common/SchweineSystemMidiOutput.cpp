#include "SchweineSystemMidiOutput.h"

#include <SchweineSystemCommon.h>

SchweineSystem::MidiOutput::MidiOutput(const std::string& targetDeviceName)
   : targetDeviceName(targetDeviceName)
   , midiOutput()
{
   open();
}

SchweineSystem::MidiOutput::MidiOutput(const Midi::Device::Channel& deviceChannel)
   : MidiOutput(Common::midiInterfaceMap.at(deviceChannel))
{
}

SchweineSystem::MidiOutput::~MidiOutput()
{
   close();
}

bool SchweineSystem::MidiOutput::open()
{
   for (unsigned int port = 0; port < midiOutput.getPortCount(); port++)
   {
      const std::string deviceName = midiOutput.getPortName(port);
      //std::cout << deviceName << std::endl;

      if (targetDeviceName == deviceName)
      {
         std::cout << "connected to " << deviceName << " @ " << port << std::endl;
         midiOutput.openPort(port);
         return true;
      }
   }

   return false;
}

void SchweineSystem::MidiOutput::close()
{
   if (!midiOutput.isPortOpen())
      return;

   midiOutput.closePort();
}

bool SchweineSystem::MidiOutput::connected()
{
   return midiOutput.isPortOpen();
}

void SchweineSystem::MidiOutput::sendNoteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity)
{
   if (!midiOutput.isPortOpen())
      return;

   if (0 == channel || channel > 16)
   {
      std::cerr << "invalid midi channel" << std::endl;
      return;
   }

   std::vector<unsigned char> onMessage(3);
   onMessage[0] = (Midi::Event::NoteOn | (channel - 1));
   onMessage[1] = note.midiValue;
   onMessage[2] = velocity;
   sendMessage(onMessage);
}

void SchweineSystem::MidiOutput::sendNoteOff(const Midi::Channel& channel, const Note& note)
{
   if (!midiOutput.isPortOpen())
      return;

   if (0 == channel || channel > 16)
   {
      std::cerr << "invalid midi channel" << std::endl;
      return;
   }

   std::vector<unsigned char> offMessage(3);
   offMessage[0] = (Midi::Event::NoteOff | (channel - 1));
   offMessage[1] = note.midiValue;
   offMessage[2] = 64;
   sendMessage(offMessage);
}

void SchweineSystem::MidiOutput::sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)
{
   if (!midiOutput.isPortOpen())
      return;

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

void SchweineSystem::MidiOutput::sendMessage(const std::vector<uint8_t>& message)
{
   midiOutput.sendMessage(message.data(), message.size());
}
