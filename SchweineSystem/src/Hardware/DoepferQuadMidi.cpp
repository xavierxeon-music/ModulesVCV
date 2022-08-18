#include "DoepferQuadMidi.h"
#include "DoepferQuadMidiPanel.h"

#include <SchweineSystemMaster.h>

DoepferQuadMidi::NoteBuffer::NoteBuffer(uint8_t index, uint8_t channel, uint8_t key)
   : index(index)
   , channel(channel)
   , key(key)
{
}

bool DoepferQuadMidi::NoteBuffer::operator==(const NoteBuffer& other) const
{
   if (index != other.index)
      return false;
   if (channel != other.channel)
      return false;
   if (key != other.key)
      return false;

   return true;
}

std::ostream& operator<<(std::ostream& os, const DoepferQuadMidi::NoteBuffer& buffer)
{
   os << (uint16_t)buffer.index << " " << (uint16_t)buffer.channel << " " << Note::fromMidi(buffer.key).name;
   return os;
}

// class

DoepferQuadMidi::DoepferQuadMidi()
   : SchweineSystem::Module()
   , SchweineSystem::MidiOutput(Midi::Device::DopeferQuad1)
   , SchweineSystem::Exapnder<SchweineSystem::BusMidi>(this)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , bufferList()
   , wasRunning(false)
{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();

   connectionButton.setDefaultColor(SchweineSystem::Color{0, 255, 0});
   connectToMidiDevice();
}

void DoepferQuadMidi::process(const ProcessArgs& args)
{
   SchweineSystem::BusMidi busMessage = receiveFromLeft();
   sendToRight(busMessage);

   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (!connected())
      return;

   processBusMessage(busMessage);
}

void DoepferQuadMidi::connectToMidiDevice()
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
}

void DoepferQuadMidi::processBusMessage(const SchweineSystem::BusMidi& busMessage)
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
         const SchweineSystem::BusMidi::Channel& busChannel = busMessage.channels[index];
         if (busChannel.noteOffEventMap.find(tick) != busChannel.noteOffEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = busChannel.noteOffEventMap.at(tick);
            for (const Sequencer::Track::NoteEvent& noteEvent : eventList)
            {
               NoteBuffer buffer(index, noteEvent.channel, noteEvent.key);
               sendNoteOff(noteEvent.channel, Note::fromMidi(noteEvent.key));

               bufferList.push_back(buffer);
            }
         }
         if (busChannel.noteOnEventMap.find(tick) != busChannel.noteOnEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = busChannel.noteOnEventMap.at(tick);
            for (const Sequencer::Track::NoteEvent& noteEvent : eventList)
            {
               NoteBuffer buffer(index, noteEvent.channel, noteEvent.key);
               sendNoteOn(noteEvent.channel, Note::fromMidi(noteEvent.key), noteEvent.velocity);

               bufferList.remove(buffer);
            }
         }
      }
   }
}

// widget

DoepferQuadMidiWidget::DoepferQuadMidiWidget(DoepferQuadMidi* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelDoepferQuadMidi = SchweineSystem::Master::the()->addModule<DoepferQuadMidi, DoepferQuadMidiWidget>("DoepferQuadMidi");
