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

MidiBusModule::MidiBusModule(const Midi::Device::Channel& deviceChannel, Sy::Module* module)
   : Sy::MidiOutput(deviceChannel)
   , Sy::Exapnder<BusMidi>(module)
   , bufferList()
   , wasRunning(false)

{
}

void MidiBusModule::processBusMessage(const BusMidi& busMessage)
{
   const bool isRunning = (Tempo::Running == busMessage.runState) || (Tempo::FirstTick == busMessage.runState);

   if (!isRunning)
   {
      if (wasRunning)
      {
         for (const NoteBuffer& buffer : bufferList)
            sendNoteOff(buffer.channel, Note::fromMidi(buffer.key));
      }
      wasRunning = isRunning;
      return;
   }
   else
   {
      if (!wasRunning)
      {
         for (const NoteBuffer& buffer : bufferList)
            sendNoteOn(buffer.channel, Note::fromMidi(buffer.key), 100);
      }
      wasRunning = isRunning;
   }

   if (Tempo::Reset == busMessage.runState)
      bufferList.clear();

   if (!busMessage.hasEvents)
      return;

   for (Sequencer::Tick tick = busMessage.startTick; tick <= busMessage.endTick; tick++)
   {
      for (uint8_t index = 0; index < 16; index++)
      {
         const BusMidi::Channel& busChannel = busMessage.channels[index];

         if (busChannel.noteOffEventMap.find(tick) != busChannel.noteOffEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = busChannel.noteOffEventMap.at(tick);
            for (const Sequencer::Track::NoteEvent& noteEvent : eventList)
            {
               NoteBuffer buffer(noteEvent.channel, noteEvent.key);
               sendNoteOff(noteEvent.channel, Note::fromMidi(noteEvent.key));

               bufferList.remove(buffer);
            }
         }

         if (busChannel.noteOnEventMap.find(tick) != busChannel.noteOnEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = busChannel.noteOnEventMap.at(tick);
            for (const Sequencer::Track::NoteEvent& noteEvent : eventList)
            {
               NoteBuffer buffer(noteEvent.channel, noteEvent.key);
               sendNoteOn(noteEvent.channel, Note::fromMidi(noteEvent.key), noteEvent.velocity);

               bufferList.push_back(buffer);
            }
         }
      }
   }
}
