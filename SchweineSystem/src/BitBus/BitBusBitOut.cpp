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
   registerAsBusModule<Data>();

   outputList.append({Panel::BitOut8, Panel::BitOut7, Panel::BitOut6, Panel::BitOut5, Panel::BitOut4, Panel::BitOut3, Panel::BitOut2, Panel::BitOut1});
}

BitBus::BitOut::~BitOut()
{
}

void BitBus::BitOut::process(const ProcessArgs& args)
{
   Data data;

   if (busModule<Data>(Side::Right))
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   if (!busModule<Data>(Side::Left))
   {
      busInIndicator.setOff();
   }
   else
   {
      busInIndicator.setOn();
      data = getBusData<Data>(Side::Left);
   }

   // sound
   for (uint8_t index = 0; index < 8; index++)
      outputList[index]->setNumberOfChannels(data.channelCount);

   for (uint8_t channel = 0; channel < data.channelCount; channel++)
   {
      const BoolField8 boolField = data.byte[channel];
      for (uint8_t index = 0; index < 8; index++)
      {
         const bool value = boolField.get(index);
         outputList[index]->setVoltage(value ? 5.0 : 0.0);
      }
   }

   if (busModule<Data>(Side::Right))
      sendBusData<Data>(Side::Right, data);
}

// widget

BitBus::BitOutWidget::BitOutWidget(BitBus::BitOut* module)
   : Svin::ModuleWidget(module)
{
   setup();
}
// creete module
Model* modelBitBusBitOut = Svin::Origin::the()->addModule<BitBus::BitOut, BitBus::BitOutWidget>("BitBusBitOut");
