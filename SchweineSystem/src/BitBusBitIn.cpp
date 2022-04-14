#include "BitBusBitIn.h"
#include "BitBusBitInPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystem.h"

using Panel = BitBusBitIn::Panel;

static const std::vector<Panel::InputId> inputId = {Panel::BitIn8, Panel::BitIn7, Panel::BitIn6, Panel::BitIn5, Panel::BitIn4, Panel::BitIn3, Panel::BitIn2, Panel::BitIn1};

BitBusBitIn::BitBusBitIn()
   : Module()
   , BitBusCommon(this)
{
   setup();
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
      lights[Panel::Blue_BusIn].setBrightness(1.0);
      boolFieldBus = getByteFromBus();
   }
   else
   {
      lights[Panel::Blue_BusIn].setBrightness(0.0);
   }

   if (!canSendBusMessage())
   {
      lights[Panel::Blue_BusOut].setBrightness(0.0);
      return;
   }
   else
   {
      lights[Panel::Blue_BusOut].setBrightness(1.0);
   }

   BoolField8 boolField = 0;

   for (uint8_t index = 0; index < 8; index++)
   {
      bool value = false;
      if (inputs[inputId.at(index)].isConnected())
         value = (inputs[inputId.at(index)].getVoltage() > 3.0);
      else
         value = boolFieldBus.get(index);

      boolField.set(index, value);
   }

   sendByteToBus(boolField);
}

Model* modelBitBusBitIn = SchweineSystem::the()->addModule<BitBusBitIn, BitBusBitInWidget>("BitBusBitIn", SchweineSystem::Series::None);

