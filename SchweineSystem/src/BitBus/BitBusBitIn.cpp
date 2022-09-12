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
   BitBusMessage message;

   if (canCommunicatWithLeft())
   {
      busInIndicator.setOn();
      message = receiveFromLeft();
   }
   else
   {
      busInIndicator.setOff();
      message.channelCount = inputList[0]->getNumberOfChannels();
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

   // sound
   for (uint8_t channel = 0; channel < message.channelCount; channel++)
   {
      BoolField8 boolField = message.byte[channel];
      for (uint8_t index = 0; index < 8; index++)
      {
         if (!inputList[index]->isConnected())
            continue;

         const bool value = (inputList[index]->getVoltage() > 3.0);
         boolField.set(index, value);
      }
      message.byte[channel] = boolField;

      sendToRight(message);
   }

   if (canCommunicatWithRight())
      sendToRight(message);
}

// widget

BitBusBitInWidget::BitBusBitInWidget(BitBusBitIn* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusBitIn = Svin::Origin::the()->addModule<BitBusBitIn, BitBusBitInWidget>("BitBusBitIn");
