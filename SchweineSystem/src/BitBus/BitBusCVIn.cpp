#include "BitBusCVIn.h"
#include "BitBusCVInPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystemMaster.h"

BitBusCVIn::BitBusCVIn()
   : Module()
   , BitBusCommon(this)
   , inputMapper(-5.0, 5.0, 0.0, 255.0)
{
   setup();

   busOutIndicator.assign(Panel::Red_BusOut);
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
      busOutIndicator.setOff();
      return;
   }

   busOutIndicator.setOn();

   BoolField8 boolField = 0;
   if (inputs[Panel::CVIn].isConnected())
   {
      const float voltageInput = inputs[Panel::CVIn].getVoltage(); // from -5.0 V to + 5.0 V
      boolField = static_cast<uint8_t>(inputMapper(voltageInput));
   }

   sendByteToBus(boolField);
}

Model* modelBitBusCVIn = SchweineSystem::Master::the()->addModule<BitBusCVIn, BitBusCVInWidget>("BitBusCVIn");
