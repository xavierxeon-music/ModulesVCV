#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystem.h"

using Panel = BitBusMeterAndFreeze::Panel;

static const std::vector<Panel::LightId> lightId = {Panel::Red_Bit8, Panel::Red_Bit7, Panel::Red_Bit6, Panel::Red_Bit5, Panel::Red_Bit4, Panel::Red_Bit3, Panel::Red_Bit2, Panel::Red_Bit1};

BitBusMeterAndFreeze::BitBusMeterAndFreeze()
   : Module()
   , BitBusCommon(this)
{
   setup();
}

BitBusMeterAndFreeze::~BitBusMeterAndFreeze()
{
}

void BitBusMeterAndFreeze::onAdd(const AddEvent& e)
{
   (void)e;
   registerBusInput();
   registerBusOutput();
}

void BitBusMeterAndFreeze::process(const ProcessArgs& args)
{
   if (canSendBusMessage())
      lights[Panel::Blue_BusOut].setBrightness(1.0);
   else
      lights[Panel::Blue_BusOut].setBrightness(0.0);

   BoolField8 boolField = 0;
   if (!canReceiveBusMessage())
   {
      lights[Panel::Blue_BusIn].setBrightness(0.0);
   }
   else
   {
      lights[Panel::Blue_BusIn].setBrightness(1.0);
      boolField = getByteFromBus();
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = boolField.get(index);
      lights[lightId.at(index)].setBrightness(value ? 1.0 : 0.0);
   }

   if (canSendBusMessage())
      sendByteToBus(boolField);
}

Model* modelBitBusMeterAndFreeze = SchweineSystem::the()->addModule<BitBusMeterAndFreeze, BitBusMeterAndFreezeWidget>("BitBusMeterAndFreeze", SchweineSystem::Series::None);

