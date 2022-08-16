#include "DoepferQuadMidi.h"
#include "DoepferQuadMidiPanel.h"

#include <SchweineSystemMaster.h>

DoepferQuadMidi::DoepferQuadMidi()
   : SchweineSystem::Module()
   , SchweineSystem::MidiOutput(Midi::Device::DopeferQuad1)
   , SchweineSystem::Exapnder<SchweineSystem::BusMidi>(this)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)

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

   for (Sequencer::Tick tick = busMessage.startTick; tick <= busMessage.endTick; tick++)
   {
      for (uint8_t index = 0; index < 16; index++)
      {
         const SchweineSystem::BusMidi::Channel& busChannel = busMessage.channels[index];

         if (busChannel.noteOffEventMap.find(tick) != busChannel.noteOffEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = busChannel.noteOffEventMap.at(tick);
            for (const Sequencer::Track::NoteEvent& noteEvent : eventList)
               sendNoteOff(noteEvent.channel, Note::fromMidi(noteEvent.key));
         }
         if (busChannel.noteOnEventMap.find(tick) != busChannel.noteOnEventMap.end())
         {
            const Sequencer::Track::NoteEvent::List& eventList = busChannel.noteOnEventMap.at(tick);
            for (const Sequencer::Track::NoteEvent& noteEvent : eventList)
               sendNoteOn(noteEvent.channel, Note::fromMidi(noteEvent.key), noteEvent.velocity);
         }
      }
   }
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

// widget

DoepferQuadMidiWidget::DoepferQuadMidiWidget(DoepferQuadMidi* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelDoepferQuadMidi = SchweineSystem::Master::the()->addModule<DoepferQuadMidi, DoepferQuadMidiWidget>("DoepferQuadMidi");
