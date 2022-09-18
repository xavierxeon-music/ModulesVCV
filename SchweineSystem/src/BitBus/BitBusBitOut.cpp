#include "BitBusBitOut.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBusBitOut::BitBusBitOut()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
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
   BitBusMessage message;

   if (canCommunicatWithRight())
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   if (!canCommunicatWithLeft())
   {
      busInIndicator.setOff();
   }
   else
   {
      busInIndicator.setOn();
      message = receiveFromLeft();
   }

   // sound
   for (uint8_t index = 0; index < 8; index++)
      outputList[index]->setNumberOfChannels(message.channelCount);

   for (uint8_t channel = 0; channel < message.channelCount; channel++)
   {
      const BoolField8 boolField = message.byte[channel];
      for (uint8_t index = 0; index < 8; index++)
      {
         const bool value = boolField.get(index);
         outputList[index]->setVoltage(value ? 5.0 : 0.0);
      }
   }

   if (canCommunicatWithRight())
      sendToRight(message);
}

// widget

BitBusBitOutWidget::BitBusBitOutWidget(BitBusBitOut* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// creete module
Model* modelBitBusBitOut = Svin::Origin::the()->addModule<BitBusBitOut, BitBusBitOutWidget>("BitBusBitOut");

