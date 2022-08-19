#include "DoepferQuadMidi.h"
#include "DoepferQuadMidiPanel.h"

#include <SchweineSystemMaster.h>

DoepferQuadMidi::DoepferQuadMidi()
   : SchweineSystem::Module()
   , MidiBusModule(Midi::Device::DopeferQuad1, this)
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

// widget

DoepferQuadMidiWidget::DoepferQuadMidiWidget(DoepferQuadMidi* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelDoepferQuadMidi = SchweineSystem::Master::the()->addModule<DoepferQuadMidi, DoepferQuadMidiWidget>("DoepferQuadMidi");
