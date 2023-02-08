#include "MidiCV.h"

#include <Music/Note.h>

#include <SvinOrigin.h>

#include <SvinMidiBus.h>

MidiCV::MidiCV()
   : Svin::Module()
   , Midi::Parser()
   , pitchOutput(this, Panel::Pitch)
   , gateOutput(this, Panel::Gate)
   , velocityOutput(this, Panel::Velocity)
   , pitchBuffer{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
   , gateBuffer{false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}
   , velocityBuffer{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
{
   setup();
   registerAsBusModule<Svin::MidiBus::Message>();
}

void MidiCV::process(const ProcessArgs& args)
{
   Svin::MidiBus::Message busMessage = getBusData<Svin::MidiBus::Message>(Side::Left);
   sendBusData<Svin::MidiBus::Message>(Side::Right, busMessage);

   pitchOutput.setNumberOfChannels(busMessage.noOfChannels);
   gateOutput.setNumberOfChannels(busMessage.noOfChannels);
   velocityOutput.setNumberOfChannels(busMessage.noOfChannels);

   const bool isRunning = (Tempo::Running == busMessage.runState) || (Tempo::FirstTick == busMessage.runState);
   if (!isRunning)
   {
      resetBuffer();
   }
   else
   {
      for (uint8_t channel = 0; channel < busMessage.noOfChannels; channel++)
      {
         if (!busMessage.channels[channel].hasEvents)
            continue;

         const Midi::Sequence::MessageList& messageList = busMessage.channels[channel].messageList;
         for (const Bytes& message : messageList)
            prcocessMessage(message);
      }
   }

   for (uint8_t index = 0; index < 16; index++)
   {
      pitchOutput.setVoltage(pitchBuffer[index], index);
      gateOutput.setActive(gateBuffer[index], index);
      velocityOutput.setVoltage(velocityBuffer[index], index);
   }
}

void MidiCV::noteOn(const Midi::Channel& channel, const uint8_t& midiNote, const Midi::Velocity& velocity)
{
   Note note = Note::fromMidi(midiNote);

   const uint8_t index = channel - 1;
   pitchBuffer[index] = note.voltage;
   gateBuffer[index] = true;
   velocityBuffer[index] = velocity;
}

void MidiCV::noteOff(const Midi::Channel& channel, const uint8_t& midiNote)
{
   (void)midiNote;

   const uint8_t index = channel - 1;
   pitchBuffer[index] = 0.0;
   gateBuffer[index] = false;
   velocityBuffer[index] = 0.0;
}

void MidiCV::resetBuffer()
{
   for (uint8_t index = 0; index < 16; index++)
   {
      pitchBuffer[index] = 0.0;
      gateBuffer[index] = false;
      velocityBuffer[index] = 0.0;
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

