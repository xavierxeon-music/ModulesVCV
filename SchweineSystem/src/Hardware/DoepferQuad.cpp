#include "DoepferQuad.h"

#include <SvinOrigin.h>

DoepferQuad::DoepferQuad()
   : Svin::Module()
   , MidiBusModule(Midi::Device::DopeferQuad1, this)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
{
   setup();
   registerAsBusModule<MidiBus>();

   connectionButton.setDefaultColor(Color{0, 255, 0});
   connectToMidiDevice();
}

void DoepferQuad::process(const ProcessArgs& args)
{
   MidiBus busMessage = getBusData<MidiBus>(Side::Left);
   sendBusData<MidiBus>(Side::Right, busMessage);

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

// create module
Model* modelDoepferQuad = Svin::Origin::the()->addModule<DoepferQuad, DoepferQuadWidget>("DoepferQuad");

