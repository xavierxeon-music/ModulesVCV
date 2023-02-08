#include "DoepferQuad.h"

#include <SvinOrigin.h>

DoepferQuad::DoepferQuad()
   : Svin::Module()
   , Svin::MidiBus::Module(Midi::Device::DopeferQuad1, this)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
{
   setup();
   registerAsBusModule<Svin::MidiBus::Message>();

   connectionButton.setDefaultColor(Color::Predefined::Green);
   connectToMidiDevice();
}

void DoepferQuad::process(const ProcessArgs& args)
{
   Svin::MidiBus::Message busMessage = getBusData<Svin::MidiBus::Message>(Side::Left);
   sendBusData<Svin::MidiBus::Message>(Side::Right, busMessage);

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

