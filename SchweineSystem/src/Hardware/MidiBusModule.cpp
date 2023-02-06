#include "MidiBusModule.h"

MidiBusModule::NoteBuffer::NoteBuffer(uint8_t channel, uint8_t key)
   : channel(channel)
   , key(key)
{
}

bool MidiBusModule::NoteBuffer::operator==(const NoteBuffer& other) const
{
   if (channel != other.channel)
      return false;
   if (key != other.key)
      return false;

   return true;
}

std::ostream& operator<<(std::ostream& os, const MidiBusModule::NoteBuffer& buffer)
{
   os << "ch = " << (uint16_t)buffer.channel << " @ " << Note::fromMidi(buffer.key).name;
   return os;
}

// class

MidiBusModule::MidiBusModule(const Midi::Device::Channel& deviceChannel, Svin::Module* module)
   : Svin::Midi::Output(deviceChannel)
   , bufferList()
   , wasRunning(false)
{
}

void MidiBusModule::processBusMessage(const MidiBus& busMessage)
{
   const bool isRunning = (Tempo::Running == busMessage.runState) || (Tempo::FirstTick == busMessage.runState);

   if (!isRunning)
   {
      if (wasRunning)
      {
         for (const NoteBuffer& buffer : bufferList)
            sendNoteOff(buffer.channel, buffer.key);
      }
      wasRunning = isRunning;
      return;
   }
   else
   {
      if (!wasRunning)
      {
         for (const NoteBuffer& buffer : bufferList)
            sendNoteOn(buffer.channel, buffer.key, 100);
      }
      wasRunning = isRunning;
   }

   if (Tempo::Reset == busMessage.runState)
      bufferList.clear();

   if (!busMessage.hasEvents)
      return;

}
