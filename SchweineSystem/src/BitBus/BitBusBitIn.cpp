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
   registerAsBusModule<Data>();

   inputList.append({Panel::BitIn8, Panel::BitIn7, Panel::BitIn6, Panel::BitIn5, Panel::BitIn4, Panel::BitIn3, Panel::BitIn2, Panel::BitIn1});
}

BitBus::BitIn::~BitIn()
{
}

void BitBus::BitIn::process(const ProcessArgs& args)
{
   Data data;

   if (busModule<Data>(Side::Left))
   {
      busInIndicator.setOn();
      data = getBusData<Data>(Side::Left);
   }
   else
   {
      busInIndicator.setOff();
      data.channelCount = inputList[0]->getNumberOfChannels();
   }

   if (!busModule<Data>(Side::Right))
   {
      busOutIndicator.setOff();
      return;
   }
   else
   {
      busOutIndicator.setOn();
   }

   // sound
   for (uint8_t channel = 0; channel < data.channelCount; channel++)
   {
      BoolField8 boolField = data.byte[channel];
      for (uint8_t index = 0; index < 8; index++)
      {
         if (!inputList[index]->isConnected())
            continue;

         const bool value = (inputList[index]->getVoltage() > 3.0);
         boolField.set(index, value);
      }
      data.byte[channel] = boolField;

      sendBusData<Data>(Side::Right, data);
   }

   if (busModule<Data>(Side::Right))
      sendBusData<Data>(Side::Right, data);
}

// widget

BitBus::BitInWidget::BitInWidget(BitIn* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelBitBusBitIn = Svin::Origin::the()->addModule<BitBus::BitIn, BitBus::BitInWidget>("BitBusBitIn");
