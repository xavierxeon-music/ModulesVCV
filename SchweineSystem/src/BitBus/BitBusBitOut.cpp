#include "BitBusBitOut.h"
#include "BitBusBitOutPanel.h"

#include <Tools/BoolField.h>

#include <SyMaster.h>

BitBusBitOut::BitBusBitOut()
   : Sy::Module()
   , Sy::Exapnder<BitBusMessage>(this)
   , outputList(this)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();

   outputList.append({Panel::BitOut8, Panel::BitOut7, Panel::BitOut6, Panel::BitOut5, Panel::BitOut4, Panel::BitOut3, Panel::BitOut2, Panel::BitOut1});
}

BitBusBitOut::~BitBusBitOut()
{
}

void BitBusBitOut::process(const ProcessArgs& args)
{
   if (canCommunicatWithRight())
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   BoolField8 boolField = 0;
   if (!canCommunicatWithLeft())
   {
      busInIndicator.setOff();
   }
   else
   {
      busInIndicator.setOn();
      boolField = receiveFromLeft().byte;
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = boolField.get(index);
      outputList[index]->setVoltage(value ? 5.0 : 0.0);
   }

   if (canCommunicatWithRight())
      sendToRight(BitBusMessage{boolField});
}

// widget

BitBusBitOutWidget::BitBusBitOutWidget(BitBusBitOut* module)
   : Sy::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusBitOut = Sy::Master::the()->addModule<BitBusBitOut, BitBusBitOutWidget>("BitBusBitOut");
