#include "BitBusBitIn.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBus::BitIn::BitIn()
   : Svin::Module()
   , inputList(this)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)

{
   setup();
   registerAsBusModule<Message>();

   inputList.append({Panel::BitIn8, Panel::BitIn7, Panel::BitIn6, Panel::BitIn5, Panel::BitIn4, Panel::BitIn3, Panel::BitIn2, Panel::BitIn1});
}

BitBus::BitIn::~BitIn()
{
}

void BitBus::BitIn::process(const ProcessArgs& args)
{
   Message message;

   if (busModule<Message>(Side::Left))
   {
      busInIndicator.setOn();
      message = getBusMessage<Message>(Side::Left);
   }
   else
   {
      busInIndicator.setOff();
      message.channelCount = inputList[0]->getNumberOfChannels();
   }

   if (!busModule<Message>(Side::Right))
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

      sendBusMessage<Message>(Side::Right, message);
   }

   if (busModule<Message>(Side::Right))
      sendBusMessage<Message>(Side::Right, message);
}

// widget

BitBus::BitInWidget::BitInWidget(BitIn* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusBitIn = Svin::Origin::the()->addModule<BitBus::BitIn, BitBus::BitInWidget>("BitBusBitIn");
