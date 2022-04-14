#include "BitBusBitOut.h"
#include "BitBusBitOutPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystem.h"

using Panel = BitBusBitOut::Panel;

static const std::vector<Panel::OutputId> outputId = {Panel::BitOut8, Panel::BitOut7, Panel::BitOut6, Panel::BitOut5, Panel::BitOut4, Panel::BitOut3, Panel::BitOut2, Panel::BitOut1};

BitBusBitOut::BitBusBitOut()
   : Module()
   , BitBusCommon(this)
{
   setup();
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
      lights[Panel::Green_BusOut].setBrightness(1.0);
   else
      lights[Panel::Green_BusOut].setBrightness(0.0);

   BoolField8 boolField = 0;
   if (!canReceiveBusMessage())
   {
      lights[Panel::Green_BusIn].setBrightness(0.0);
   }
   else
   {
      lights[Panel::Green_BusIn].setBrightness(1.0);
      boolField = getByteFromBus();
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = boolField.get(index);
      outputs[outputId.at(index)].setVoltage(value ? 5.0 : 0.0);
   }

   if (canSendBusMessage())
      sendByteToBus(boolField);
}

Model* modelBitBusBitOut = SchweineSystem::the()->addModule<BitBusBitOut, BitBusBitOutWidget>("BitBusBitOut", SchweineSystem::Series::None);

