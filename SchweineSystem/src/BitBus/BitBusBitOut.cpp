#include "BitBusBitOut.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBus::BitOut::BitOut()
   : Svin::Module()
   , outputList(this)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   registerAsBusModule<Message>();

   outputList.append({Panel::BitOut8, Panel::BitOut7, Panel::BitOut6, Panel::BitOut5, Panel::BitOut4, Panel::BitOut3, Panel::BitOut2, Panel::BitOut1});
}

BitBus::BitOut::~BitOut()
{
}

void BitBus::BitOut::process(const ProcessArgs& args)
{
   Message message;

   if (busModule<Message>(Side::Right))
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   if (!busModule<Message>(Side::Left))
   {
      busInIndicator.setOff();
   }
   else
   {
      busInIndicator.setOn();
      message = getBusMessage<Message>(Side::Left);
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

   if (busModule<Message>(Side::Right))
      sendBusMessage<Message>(Side::Right, message);
}

// widget

BitBus::BitOutWidget::BitOutWidget(BitBus::BitOut* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// creete module
Model* modelBitBusBitOut = Svin::Origin::the()->addModule<BitBus::BitOut, BitBus::BitOutWidget>("BitBusBitOut");
