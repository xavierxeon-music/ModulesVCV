#include "DrumTrigger.h"

DrumTrigger::DrumTrigger()
   : Svin::Module()
   , Svin::Midi::Output(Midi::Device::DrumTrigger)
   , input(this, Panel::Input)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
   , flank{}
{
   setup();

   connectionButton.setDefaultColor(Color(0, 255, 0));
   connectToMidiDevice();
}

void DrumTrigger::connectToMidiDevice()
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

void DrumTrigger::process(const ProcessArgs& args)
{
   if (connectionButton.isTriggered())
      connectToMidiDevice();

   static const uint8_t midiBaseNote = Note::availableNotes.at(1).midiValue + 12;

   const uint8_t maxIndex = input.getNumberOfChannels();
   for (uint8_t index = 0; index < maxIndex; index++)
   {
      const bool on = input.isOn(index);
      const Flank::State state = flank[index].observe(on);

      if (Flank::State::Rising == state)
         sendNoteOn(10, Note::fromMidi(midiBaseNote + index), 127);
      else if (Flank::State::Falling == state)
         sendNoteOff(10, Note::fromMidi(midiBaseNote + index));
   }
}

// widget

DrumTriggerWidget::DrumTriggerWidget(DrumTrigger* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelDrumTrigger = Svin::Origin::the()->addModule<DrumTrigger, DrumTriggerWidget>("DrumTrigger");
