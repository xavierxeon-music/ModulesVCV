#include "BitBusBitOut.h"
#include "BitBusBitOutPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystemMaster.h"

BitBusBitOut::BitBusBitOut()
   : Module()
   , BitBusCommon(this)
   , outputList(outputs)
{
   setup();

   outputList.append({Panel::BitOut8, Panel::BitOut7, Panel::BitOut6, Panel::BitOut5, Panel::BitOut4, Panel::BitOut3, Panel::BitOut2, Panel::BitOut1});
   busInIndicator.assign(Panel::Red_BusIn);
   busOutIndicator.assign(Panel::Red_BusOut);
}

BitBusBitOut::~BitBusBitOut()
{
}

void BitBusBitOut::onAdd(const AddEvent& e)
{
   (void)e;
   registerBusInput();
   registerBusOutput();
}

void BitBusBitOut::process(const ProcessArgs& args)
{
   if (canSendBusMessage())
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   BoolField8 boolField = 0;
   if (!canReceiveBusMessage())
   {
      busInIndicator.setOff();
   }
   else
   {
      busInIndicator.setOn();
      boolField = getByteFromBus();
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = boolField.get(index);
      outputList[index]->setVoltage(value ? 5.0 : 0.0);
   }

   if (canSendBusMessage())
      sendByteToBus(boolField);
}

Model* modelBitBusBitOut = SchweineSystem::Master::the()->addModule<BitBusBitOut, BitBusBitOutWidget>("BitBusBitOut");
