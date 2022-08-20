#include "DoepferQuad.h"
#include "DoepferQuadPanel.h"

#include <SchweineSystemMaster.h>

DoepferQuad::DoepferQuad()
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

void DoepferQuad::process(const ProcessArgs& args)
{
   SchweineSystem::BusMidi busMessage = receiveFromLeft();
   sendToRight(busMessage);

   if (connectionButton.isTriggered())
      connectToMidiDevice();

   if (!connected())
      return;

   processBusMessage(busMessage);
}

void DoepferQuad::connectToMidiDevice()
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

DoepferQuadWidget::DoepferQuadWidget(DoepferQuad* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelDoepferQuad = SchweineSystem::Master::the()->addModule<DoepferQuad, DoepferQuadWidget>("DoepferQuad");
