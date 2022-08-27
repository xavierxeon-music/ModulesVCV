#include "SvinMidiOutput.h"

const Svin::Common::MidiInterfaceMap Svin::Common::midiInterfaceMap = {
   {Midi::Device::Splitter, "ESI M4U eX Port 4"},
   {Midi::Device::DopeferQuad1, "ESI M4U eX Port 1"},
   {Midi::Device::DopeferQuad2, "ESI M4U eX Port 1"},
   {Midi::Device::DopeferQuad3, "ESI M4U eX Port 1"},
   {Midi::Device::DopeferQuad4, "ESI M4U eX Port 1"},
   {Midi::Device::KeyStep1, "ESI M4U eX Port 5"},
   {Midi::Device::KeyStep2, "ESI M4U eX Port 5"},
   {Midi::Device::KeyStep3, "ESI M4U eX Port 6"},
   {Midi::Device::KeyStep4, "ESI M4U eX Port 6"},
   {Midi::Device::Daisy, "ESI M4U eX Port 4"},
   {Midi::Device::DrumTrigger, "ESI M4U eX Port 5"},
   {Midi::Device::VCMC, "VCMC"},
   {Midi::Device::Metropolix, "Metropolix"},
   {Midi::Device::FlameCC, "ESI M4U eX Port 7"},
   {Midi::Device::BitBox, "ESI M4U eX Port 4"},
   {Midi::Device::BitBoxMicro, "ESI M4U eX Port 4"},
   {Midi::Device::Unused, ""},
};

Svin::MidiOutput::MidiOutput(const std::string& targetDeviceName)
   : targetDeviceName(targetDeviceName)
   , midiOutput()
{
   open();
}

Svin::MidiOutput::MidiOutput(const Midi::Device::Channel& deviceChannel)
   : MidiOutput(Common::midiInterfaceMap.at(deviceChannel))
{
}

Svin::MidiOutput::~MidiOutput()
{
   close();
}

bool Svin::MidiOutput::open()
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

void Svin::MidiOutput::close()
{
   if (!midiOutput.isPortOpen())
      return;

   midiOutput.closePort();
}

bool Svin::MidiOutput::connected()
{
   return midiOutput.isPortOpen();
}

void Svin::MidiOutput::sendNoteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity)
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

void Svin::MidiOutput::sendNoteOff(const Midi::Channel& channel, const Note& note)
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

void Svin::MidiOutput::sendControllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value)
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

void Svin::MidiOutput::sendMessage(const std::vector<uint8_t>& message)
{
   midiOutput.sendMessage(message.data(), message.size());
}
