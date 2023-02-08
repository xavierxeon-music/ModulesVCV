#include "MidiMize.h"

// state

MidiMize::State::State()
   : State(24, false, 0)
{
}

MidiMize::State::State(const uint8_t midiNote, const bool gate, const uint8_t velocity)
   : midiNote(midiNote)
   , gate(gate)
   , velocity(velocity)
{
}

bool MidiMize::State::operator==(const State& other) const
{
   if (midiNote != other.midiNote)
      return false;
   if (gate != other.gate)
      return false;
   if (velocity != other.velocity)
      return false;

   return true;
}

// midi mize

MidiMize::MidiMize()
   : Svin::Module()
   , pitchInput(this, Panel::Pitch)
   , gateInput(this, Panel::Gate)
   , velocityInput(this, Panel::Velocity)
   , velocityMapper(0.0, 10.0, 0.0, 127.0)
   , lastState{}
{
   setup();
   registerAsBusModule<Svin::Midi::Bus>();
}

void MidiMize::process(const ProcessArgs& args)
{
   Svin::Midi::Bus busMessage;
   busMessage.runState = Tempo::Running;

   const uint8_t noOfChannels = pitchInput.isConnected() ? pitchInput.getNumberOfChannels() : 0;
   busMessage.noOfChannels = noOfChannels;

   for (uint8_t channel = 0; channel < noOfChannels; channel++)
   {
      const float& voltage = pitchInput.getVoltage(channel);
      const uint8_t midiNote = Note::fromVoltage(voltage).midiValue;
      const bool gate = gateInput.isOn(channel);
      const uint8_t velocity = velocityInput.isConnected() ? velocityMapper(velocityInput.getVoltage(channel)) : 127;

      const State state(midiNote, gate, velocity);
      if (state == lastState[channel])
         continue;

      Svin::Midi::Bus::Channel& busChannel = busMessage.channels[channel];
      if (!state.gate && !lastState[channel].gate) // both off therfore no change
      {
         continue;
      }
      else if (state.gate && !lastState[channel].gate) // from on to off
      {
         busChannel.hasEvents = true;

         const Bytes offMessage = noteOff(channel, lastState[channel].midiNote);
         busChannel.messageList.push_back(offMessage);
      }
      else if (!state.gate && lastState[channel].gate) // from off to on
      {
         busChannel.hasEvents = true;

         const Bytes onMessage = noteOn(channel, state.midiNote, state.velocity);
         busChannel.messageList.push_back(onMessage);
      }
      else // both on therefore pitch or velocity change
      {
         busChannel.hasEvents = true;

         const Bytes offMessage = noteOff(channel, lastState[channel].midiNote);
         busChannel.messageList.push_back(offMessage);

         const Bytes onMessage = noteOn(channel, state.midiNote, state.velocity);
         busChannel.messageList.push_back(onMessage);
      }

      lastState[channel] = state;
   }

   sendBusData<Svin::Midi::Bus>(Side::Right, busMessage);
}

Bytes MidiMize::noteOn(const uint8_t& channel, const uint8_t& midiNote, const uint8_t& velocity)
{
   Bytes onMessage(3);
   onMessage[0] = (Midi::Event::NoteOn | channel);
   onMessage[1] = midiNote;
   onMessage[2] = velocity;

   return onMessage;
}

Bytes MidiMize::noteOff(const uint8_t& channel, const uint8_t& midiNote)
{
   Bytes offMessage(3);
   offMessage[0] = (Midi::Event::NoteOff | channel);
   offMessage[1] = midiNote;
   offMessage[2] = 64;

   return offMessage;
}

// widget

MidiMizeWidget::MidiMizeWidget(MidiMize* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelMidiMize = Svin::Origin::the()->addModule<MidiMize, MidiMizeWidget>("MidiMize");
