#include "MidiCV.h"

#include <Music/Note.h>

#include <SvinOrigin.h>

MidiCV::MidiCV()
   : Svin::Module()
   , pitchOutput(this, Panel::Pitch)
   , gateOutput(this, Panel::Gate)
   , velocityOutput(this, Panel::Velocity)
{
   setup();
   registerAsBusModule<MidiBus>();
}

void MidiCV::process(const ProcessArgs& args)
{
   MidiBus busMessage = getBusData<MidiBus>(Side::Left);
   sendBusData<MidiBus>(Side::Right, busMessage);

   pitchOutput.setNumberOfChannels(busMessage.noOfChannels);
   gateOutput.setNumberOfChannels(busMessage.noOfChannels);
   velocityOutput.setNumberOfChannels(busMessage.noOfChannels);

   const bool isRunning = (Tempo::Running == busMessage.runState) || (Tempo::FirstTick == busMessage.runState);
   if (!isRunning)
   {
      for (uint8_t index = 0; index < 16; index++)
      {
         pitchOutput.setVoltage(0.0, index);
         gateOutput.setOff(index);
         velocityOutput.setVoltage(0.0, index);
      }
      return;
   }

   if (busMessage.startTick >= busMessage.endTick)
      return;

   if (!busMessage.hasEvents)
      return;

   for (uint8_t index = 0; index < busMessage.noOfChannels; index++)
   {
      Sequencer::NoteEvent lastEvent;
      bool foundEvent = false;

      const MidiBus::Channel& busChannel = busMessage.channels[index];
      using ConstIterator = Sequencer::NoteEvent::TimeMap::const_iterator;

      ConstIterator itOff = busChannel.noteOffEventMap.find(busMessage.endTick);
      if (itOff != busChannel.noteOffEventMap.cend())
      {
         const Sequencer::NoteEvent::List& eventList = itOff->second;
         if (!eventList.empty())
         {
            lastEvent = eventList.at(0);
            foundEvent = true;
            debug() << "off";
         }
      }
      ConstIterator itOn = busChannel.noteOnEventMap.find(busMessage.endTick);
      if (itOn != busChannel.noteOnEventMap.cend())
      {
         const Sequencer::NoteEvent::List& eventList = itOn->second;
         if (!eventList.empty())
         {
            lastEvent = eventList.at(0);
            foundEvent = true;
            debug() << "on";
         }
      }

      if (!foundEvent)
         continue;

      debug() << "event" << lastEvent.on;

      if (lastEvent.on && busChannel.isMonophoic)
      {
         const float voltage = Note::fromMidi(lastEvent.midiNote).voltage;
         pitchOutput.setVoltage(voltage, index);

         gateOutput.setOn(index);

         const float velocity = 5.0;
         velocityOutput.setVoltage(velocity, index);
      }
      else
      {
         pitchOutput.setVoltage(0.0, index);
         gateOutput.setOff(index);

         velocityOutput.setVoltage(0.0, index);
      }
   }
}

// widget

MidiCVWidget::MidiCVWidget(MidiCV* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// create module
Model* modelMidiCV = Svin::Origin::the()->addModule<MidiCV, MidiCVWidget>("MidiCV");

