#include "DoepferQuad.h"
#include "DoepferQuadPanel.h"

#include <SyMaster.h>

DoepferQuad::DoepferQuad()
   : Sy::Module()
   , MidiBusModule(Midi::Device::DopeferQuad1, this)
   , connectionButton(this, Panel::Connect, Panel::RGB_Connect)
{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();

   connectionButton.setDefaultColor(Sy::Color{0, 255, 0});
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
: Sy::ModuleWidget(module)
{
   setup();
}

Model* modelDoepferQuad = Sy::Master::the()->addModule<DoepferQuad, DoepferQuadWidget>("DoepferQuad");
