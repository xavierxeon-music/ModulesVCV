#include "SyMidiOutput.h"

#include <SyCommon.h>

Sy::MidiOutput::MidiOutput(const std::string& targetDeviceName)
   : targetDeviceName(targetDeviceName)
   , midiOutput()
{
   open();
}

Sy::MidiOutput::MidiOutput(const Midi::Device::Channel& deviceChannel)
   : MidiOutput(Common::midiInterfaceMap.at(deviceChannel))
{
}

Sy::MidiOutput::~MidiOutput()
{
   close();
}

bool Sy::MidiOutput::open()
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

void Sy::MidiOutput::close()
{
   if (!midiOutput.isPortOpen())
      return;

   midiOutput.closePort();
}

bool Sy::MidiOutput::connected()
{
   return midiOutput.isPortOpen();
}

void Sy::MidiOutput::sendNoteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity)
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

void Sy::MidiOutput::sendNoteOff(const Midi::Channel& channel, const Note& note)
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

void Sy::MidiOutput::sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)
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

void Sy::MidiOutput::sendMessage(const std::vector<uint8_t>& message)
{
   midiOutput.sendMessage(message.data(), message.size());
}
