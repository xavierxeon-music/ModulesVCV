#include "SvinMidiBus.h"

Svin::MidiBus::Module::NoteBuffer::NoteBuffer(uint8_t channel, uint8_t key)
   : channel(channel)
   , key(key)
{
}

bool Svin::MidiBus::Module::NoteBuffer::operator==(const NoteBuffer& other) const
{
   if (channel != other.channel)
      return false;
   if (key != other.key)
      return false;

   return true;
}

// class

Svin::MidiBus::Module::Module(const ::Midi::Device::Channel& deviceChannel, Svin::Module* module)
   : Svin::Midi::Output(deviceChannel)
   , bufferList()
   , wasRunning(false)
{
}

void Svin::MidiBus::Module::processBusMessage(const Message& busMessage)
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


}
