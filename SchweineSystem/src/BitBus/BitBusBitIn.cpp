#include "BitBusBitIn.h"
#include "BitBusBitInPanel.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBusBitIn::BitBusBitIn()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , inputList(this)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)

{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();

   inputList.append({Panel::BitIn8, Panel::BitIn7, Panel::BitIn6, Panel::BitIn5, Panel::BitIn4, Panel::BitIn3, Panel::BitIn2, Panel::BitIn1});
}

BitBusBitIn::~BitBusBitIn()
{
}

void BitBusBitIn::process(const ProcessArgs& args)
{
   BoolField8 boolFieldBus = 0;

   if (canCommunicatWithLeft())
   {
      busInIndicator.setOn();
      boolFieldBus = receiveFromLeft().byte;
   }
   else
   {
      busInIndicator.setOff();
   }

   if (!canCommunicatWithRight())
   {
      busOutIndicator.setOff();
      return;
   }
   else
   {
      busOutIndicator.setOn();
   }

   BoolField8 boolField = 0;

   for (uint8_t index = 0; index < 8; index++)
   {
      bool value = false;
      if (inputList[index]->isConnected())
         value = (inputList[index]->getVoltage() > 3.0);
      else
         value = boolFieldBus.get(index);

      boolField.set(index, value);
   }

   sendToRight(BitBusMessage{boolField});
}

// widget

BitBusBitInWidget::BitBusBitInWidget(BitBusBitIn* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusBitIn = Svin::Origin::the()->addModule<BitBusBitIn, BitBusBitInWidget>("BitBusBitIn");
