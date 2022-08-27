#include "MidiCV.h"
#include "MidiCVPanel.h"

#include <Music/Note.h>

#include <SvinMaster.h>

MidiCV::MidiCV()
   : Svin::Module()
   , Svin::Exapnder<BusMidi>(this)
{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();
}

void MidiCV::process(const ProcessArgs& args)
{
   BusMidi busMessage = receiveFromLeft();
   sendToRight(busMessage);

   const bool isRunning = (Tempo::Running == busMessage.runState) || (Tempo::FirstTick == busMessage.runState);
   if (!isRunning)
   {
      const uint8_t noOfChannels = outputs[Panel::Pitch].getChannels();
      for (uint8_t index = 0; index < noOfChannels; index++)
      {
         outputs[Panel::Pitch].setVoltage(0.0, index);
         outputs[Panel::Gate].setVoltage(0.0, index);
         outputs[Panel::Velocity].setVoltage(0.0, index);
      }
      return;
   }

   if (outputs[Panel::Pitch].getChannels() != busMessage.noOfChannels)
      outputs[Panel::Pitch].setChannels(busMessage.noOfChannels);

   if (outputs[Panel::Gate].getChannels() != busMessage.noOfChannels)
      outputs[Panel::Gate].setChannels(busMessage.noOfChannels);

   if (outputs[Panel::Velocity].getChannels() != busMessage.noOfChannels)
      outputs[Panel::Velocity].setChannels(busMessage.noOfChannels);

   if (busMessage.startTick >= busMessage.endTick)
      return;

   if (!busMessage.hasEvents)
      return;

   for (uint8_t index = 0; index < busMessage.noOfChannels; index++)
   {
      Sequencer::Track::NoteEvent lastEvent;
      bool foundEvent = false;

      const BusMidi::Channel& busChannel = busMessage.channels[index];
      using ConstIterator = Sequencer::Track::NoteEvent::TimeMap::const_iterator;

      ConstIterator itOff = busChannel.noteOffEventMap.find(busMessage.endTick);
      if (itOff != busChannel.noteOffEventMap.cend())
      {
         const Sequencer::Track::NoteEvent::List& eventList = itOff->second;
         lastEvent = eventList.at(0);
         foundEvent = true;
      }

      ConstIterator itOn = busChannel.noteOnEventMap.find(busMessage.endTick);
      if (itOn != busChannel.noteOnEventMap.cend())
      {
         const Sequencer::Track::NoteEvent::List& eventList = itOn->second;
         lastEvent = eventList.at(0);
         foundEvent = true;
      }

      if (!foundEvent)
         continue;

      if (lastEvent.on && busChannel.isMonophoic)
      {
         const float voltage = Note::fromMidi(lastEvent.key).voltage;
         outputs[Panel::Pitch].setVoltage(voltage, index);

         outputs[Panel::Gate].setVoltage(5.0, index);

         const float velocity = 5.0;
         outputs[Panel::Velocity].setVoltage(velocity, index);
      }
      else
      {
         outputs[Panel::Pitch].setVoltage(0.0, index);
         outputs[Panel::Gate].setVoltage(0.0, index);
         outputs[Panel::Velocity].setVoltage(0.0, index);
      }
   }
}

// widget

MidiCVWidget::MidiCVWidget(MidiCV* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelMidiCV = Svin::Master::the()->addModule<MidiCV, MidiCVWidget>("MidiCV");
