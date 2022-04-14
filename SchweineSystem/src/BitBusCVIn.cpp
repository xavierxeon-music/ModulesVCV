#include "BitBusCVIn.h"
#include "BitBusCVInPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystem.h"

BitBusCVIn::BitBusCVIn()
   : Module()
   , BitBusCommon(this)
   , inputMapper(-5.0, 5.0, 0.0, 255.0)
{
   setup();
}

void BitBusCVIn::onAdd(const AddEvent& e)
{
   (void)e;
   registerBusOutput();
}

BitBusCVIn::~BitBusCVIn()
{
}

void BitBusCVIn::process(const ProcessArgs& args)
{
   if (!canSendBusMessage())
   {
      lights[Panel::Blue_BusOut].setBrightness(0.0);
      return;
   }

   lights[Panel::Blue_BusOut].setBrightness(1.0);

   BoolField8 boolField = 0;
   if (inputs[Panel::CVIn].isConnected())
   {
      const float voltageInput = inputs[Panel::CVIn].getVoltage(); // from -5.0 V to + 5.0 V
      boolField = static_cast<uint8_t>(inputMapper(voltageInput));
   }

   sendByteToBus(boolField);
}

Model* modelBitBusCVIn = SchweineSystem::the()->addModule<BitBusCVIn, BitBusCVInWidget>("BitBusCVIn", SchweineSystem::Series::None);

