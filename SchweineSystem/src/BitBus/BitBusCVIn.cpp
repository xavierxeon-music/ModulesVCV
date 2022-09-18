#include "BitBusCVIn.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBusCVIn::BitBusCVIn()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , cvInput(this, Panel::CVIn)
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
   // optics
   if (!canCommunicatWithRight())
   {
      busOutIndicator.setOff();
      return;
   }

   busOutIndicator.setOn();

   // sound
   BitBusMessage message;
   if (cvInput.isConnected())
   {
      message.channelCount = cvInput.getNumberOfChannels();
      for (uint8_t channel = 0; channel < message.channelCount; channel++)
      {
         const float voltageInput = cvInput.getVoltage(channel); // from -5.0 V to + 5.0 V
         message.byte[channel] = static_cast<uint8_t>(inputMapper(voltageInput));
      }
   }

   sendToRight(message);
}

// widget

BitBusCVInWidget::BitBusCVInWidget(BitBusCVIn* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusCVIn = Svin::Origin::the()->addModule<BitBusCVIn, BitBusCVInWidget>("BitBusCVIn");

