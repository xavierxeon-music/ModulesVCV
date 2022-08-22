#include "BitBusCVIn.h"
#include "BitBusCVInPanel.h"

#include <Tools/BoolField.h>

#include "SyMaster.h"

BitBusCVIn::BitBusCVIn()
   : Sy::Module()
   , Sy::Exapnder<BitBusMessage>(this)
   , inputMapper(-5.0, 5.0, 0.0, 255.0)
   , busOutIndicator(this, Panel::RGB_BusOut)

{
   setup();
   allowExpanderOnRight();
}

BitBusCVIn::~BitBusCVIn()
{
}

void BitBusCVIn::process(const ProcessArgs& args)
{
   if (!canCommunicatWithRight())
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
   : Sy::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusCVIn = Sy::Master::the()->addModule<BitBusCVIn, BitBusCVInWidget>("BitBusCVIn");
