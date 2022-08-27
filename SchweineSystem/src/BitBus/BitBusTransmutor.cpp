#include "BitBusTransmutor.h"
#include "BitBusTransmutorPanel.h"

#include <Tools/BoolField.h>

#include <SvinMaster.h>

BitBusTransmutor::BitBusTransmutor()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , displayButton(this, Panel::Display)
   , displayController(this, Panel::Pixels_Display)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();

   allowExpanderOnLeft();
   allowExpanderOnRight();
}

void BitBusTransmutor::load(const Svin::Json::Object& rootObject)
{
}

void BitBusTransmutor::save(Svin::Json::Object& rootObject)
{
}

void BitBusTransmutor::process(const ProcessArgs& args)
{
   if (!canCommunicatWithLeft())
      return busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!canCommunicatWithRight())
      return busOutIndicator.setOff();
   else
      busOutIndicator.setOn();

   const BoolField8 boolFieldIn = receiveFromLeft().byte;
   BoolField8 boolFieldOut = boolFieldIn;

   sendToRight(BitBusMessage{boolFieldOut});
}

void BitBusTransmutor::updateDisplays()
{
   displayController.fill();
}

// widget

BitBusTransmutorWidget::BitBusTransmutorWidget(BitBusTransmutor* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusTransmutor = Svin::Master::the()->addModule<BitBusTransmutor, BitBusTransmutorWidget>("BitBusTransmutor");
