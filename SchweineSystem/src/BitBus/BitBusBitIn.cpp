#include "BitBusBitIn.h"
#include "BitBusBitInPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystemMaster.h"

BitBusBitIn::BitBusBitIn()
   : Module()
   , BitBusCommon(this)
   , inputList(inputs)
{
   setup();

   inputList.append({Panel::BitIn8, Panel::BitIn7, Panel::BitIn6, Panel::BitIn5, Panel::BitIn4, Panel::BitIn3, Panel::BitIn2, Panel::BitIn1});
   busInIndicator.assign(Panel::Red_BusIn);
   busOutIndicator.assign(Panel::Red_BusOut);
}

BitBusBitIn::~BitBusBitIn()
{
}

void BitBusBitIn::onAdd(const AddEvent& e)
{
   (void)e;
   registerBusInput();
   registerBusOutput();
}

void BitBusBitIn::process(const ProcessArgs& args)
{
   BoolField8 boolFieldBus = 0;

   if (canReceiveBusMessage())
   {
      busInIndicator.setOn();
      boolFieldBus = getByteFromBus();
   }
   else
   {
      busInIndicator.setOff();
   }

   if (!canSendBusMessage())
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

   sendByteToBus(boolField);
}

Model* modelBitBusBitIn = SchweineSystem::Master::the()->addModule<BitBusBitIn, BitBusBitInWidget>("BitBusBitIn");
