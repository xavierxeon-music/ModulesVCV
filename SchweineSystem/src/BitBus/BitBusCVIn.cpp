#include "BitBusCVIn.h"
#include "BitBusCVInPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystemMaster.h"

BitBusCVIn::BitBusCVIn()
   : SchweineSystem::Module()
   , SchweineSystem::Exapnder<BitBusMessage>(this)
   , inputMapper(-5.0, 5.0, 0.0, 255.0)
   , busOutIndicator(this, Panel::RGB_BusOut)

{
   setup();

}

BitBusCVIn::~BitBusCVIn()
{
}

void BitBusCVIn::process(const ProcessArgs& args)
{
   if (!hasExpanderToRight())
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

   sendToRight(BitBusMessage {boolField});
}

// widget

BitBusCVInWidget::BitBusCVInWidget(BitBusCVIn* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusCVIn = SchweineSystem::Master::the()->addModule<BitBusCVIn, BitBusCVInWidget>("BitBusCVIn");
