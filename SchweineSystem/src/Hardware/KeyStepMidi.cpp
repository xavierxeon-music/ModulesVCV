#include "KeyStepMidi.h"
#include "KeyStepMidiPanel.h"

#include <SchweineSystemMaster.h>

KeyStepMidi::KeyStepMidi()
   : SchweineSystem::Module()
   , MidiBusModule(Midi::Device::KeyStep1, this)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)

{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();

   connectionButton.setDefaultColor(SchweineSystem::Color{0, 255, 0});
   connectToMidiDevice();
}

void KeyStepMidi::process(const ProcessArgs& args)
{
   SchweineSystem::BusMidi busMessage = receiveFromLeft();
   sendToRight(busMessage);

   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (!connected())
      return;

   processBusMessage(busMessage);
}

void KeyStepMidi::connectToMidiDevice()
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

KeyStepMidiWidget::KeyStepMidiWidget(KeyStepMidi* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelKeyStepMidi = SchweineSystem::Master::the()->addModule<KeyStepMidi, KeyStepMidiWidget>("KeyStepMidi");
