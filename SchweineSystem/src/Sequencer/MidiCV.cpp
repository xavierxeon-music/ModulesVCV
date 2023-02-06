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
}

// widget

MidiCVWidget::MidiCVWidget(MidiCV* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// create module
Model* modelMidiCV = Svin::Origin::the()->addModule<MidiCV, MidiCVWidget>("MidiCV");

