#include "MidiMize.h"

#include <Tools/Text.h>

#include "MidiReplay.h"

bool MidiMize::DrumState::operator!=(const DrumState& other) const
{
   if (active != other.active)
      return true;

   return false;
}

// midi mize

MidiMize::MidiMize()
   : Svin::Module()
   , selectKnobList(this)
   , channelDisplayList(this)
   , pitchInputList(this)
   , gateInputList(this)
   , velocityInputList(this)
   , prevNoteEvent{}
   , velocityMapper(0.0, 10.0, 0.0, 127.0)
   , drumTriggerList(this)
   , drumState{}
{
   setup();
   registerAsBusModule<MidiBus>();

   selectKnobList.append({Panel::MeloA_Select,
                          Panel::MeloB_Select,
                          Panel::MeloC_Select,
                          Panel::MeloD_Select});

   channelDisplayList.append({Panel::Text_MeloA_Channel,
                              Panel::Text_MeloB_Channel,
                              Panel::Text_MeloC_Channel,
                              Panel::Text_MeloD_Channel});

   pitchInputList.append({Panel::MeloA_Pitch,
                          Panel::MeloB_Pitch,
                          Panel::MeloC_Pitch,
                          Panel::MeloD_Pitch});

   gateInputList.append({Panel::MeloA_Gate,
                         Panel::MeloB_Gate,
                         Panel::MeloC_Gate,
                         Panel::MeloD_Gate});

   velocityInputList.append({Panel::MeloA_Velocity,
                             Panel::MeloB_Velocity,
                             Panel::MeloC_Velocity,
                             Panel::MeloD_Velocity});

   drumTriggerList.append({Panel::Drums_One_Trigger,
                           Panel::Drums_Two_Trigger,
                           Panel::Drums_Three_Trigger,
                           Panel::Drums_Four_Trigger,
                           Panel::Drums_Five_Trigger,
                           Panel::Drums_Six_Trigger,
                           Panel::Drums_Seven_Trigger,
                           Panel::Drums_Eight_Trigger});

   for (uint8_t voice = 0; voice < 4; voice++)
   {
      selectKnobList[voice]->setRange(1.0, 16.0, voice + 1);
      selectKnobList[voice]->enableSteps(true);

      channelDisplayList[voice]->setColor(Color::Predefined::Yellow);
   }
}

void MidiMize::process(const ProcessArgs& args)
{
   MidiBus busMessage;
   busMessage.runState = Tempo::Running;
   busMessage.endTick = 1;

   for (uint8_t voice = 0; voice < 4; voice++)
   {
      const Midi::Channel channel = selectKnobList[voice]->getValue();

      const Note note = Note::fromVoltage(pitchInputList[voice]->getVoltage());
      const bool gate = gateInputList[voice]->isOn();
      const uint8_t velocity = velocityMapper(velocityInputList[voice]->getVoltage());

      const Sequencer::NoteEvent currentNoteEvent(channel, note.midiValue, gate, velocity);
      if (currentNoteEvent == prevNoteEvent[voice])
         continue;

      Sequencer::NoteEvent::List offList;
      Sequencer::NoteEvent::List onList;

      if (prevNoteEvent[voice].channel != currentNoteEvent.channel)
      {
         prevNoteEvent[voice].on = false; // only used to turn off things
         offList.push_back(prevNoteEvent[voice]);
         onList.push_back(currentNoteEvent);
      }
      else if (prevNoteEvent[voice].on && !currentNoteEvent.on) // used to be on,  turn off
      {
         prevNoteEvent[voice].on = false; // only used to turn off things
         offList.push_back(prevNoteEvent[voice]);
      }
      else if (!prevNoteEvent[voice].on && currentNoteEvent.on) // used to be off, turn on
      {
         onList.push_back(currentNoteEvent);
      }
      else if ((prevNoteEvent[voice].midiNote != currentNoteEvent.midiNote) || (prevNoteEvent[voice].velocity != currentNoteEvent.velocity))
      {
         prevNoteEvent[voice].on = false; // only used to turn off things
         offList.push_back(prevNoteEvent[voice]);
         onList.push_back(currentNoteEvent);
      }

      prevNoteEvent[voice] = currentNoteEvent;

      busMessage.hasEvents = true;
      busMessage.channels[voice].isMonophoic = true;
      busMessage.channels[voice].noteOffEventMap[1] = offList;
      busMessage.channels[voice].noteOnEventMap[1] = onList;
   }

   busMessage.noOfChannels = 4;
   sendBusData<MidiBus>(Side::Right, busMessage);
}

void MidiMize::updateDisplays()
{
   for (uint8_t voice = 0; voice < 4; voice++)
   {
      const Midi::Channel channel = selectKnobList[voice]->getValue();
      const std::string channelText = Text::pad(std::to_string(channel), 2);
      channelDisplayList[voice]->setText(channelText);
   }
}

void MidiMize::load(const Svin::Json::Object& rootObject)
{
   Svin::Json::Array channelArray = rootObject.get("channel").toArray();
   for (uint8_t voice = 0; voice < 4; voice++)
      selectKnobList[voice]->setValue(channelArray.at(voice).toReal());
}

void MidiMize::save(Svin::Json::Object& rootObject)
{
   Svin::Json::Array channelArray;
   for (uint8_t voice = 0; voice < 4; voice++)
      channelArray.append(selectKnobList[voice]->getValue());

   rootObject.set("channel", channelArray);
}

// widget

MidiMizeWidget::MidiMizeWidget(MidiMize* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelMidiMize = Svin::Origin::the()->addModule<MidiMize, MidiMizeWidget>("MidiMize");

