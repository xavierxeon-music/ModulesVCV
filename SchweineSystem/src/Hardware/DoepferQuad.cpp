#include "DoepferQuad.h"

#include <SvinOrigin.h>

DoepferQuad::DoepferQuad()
   : Svin::Module()
   , MidiBusModule(Midi::Device::DopeferQuad1, this)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();

   connectionButton.setDefaultColor(Svin::Color{0, 255, 0});
   connectToMidiDevice();
}

void DoepferQuad::process(const ProcessArgs& args)
{
   BusMidi busMessage = receiveFromLeft();
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
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelDoepferQuad = Svin::Origin::the()->addModule<DoepferQuad, DoepferQuadWidget>("DoepferQuad");

