#include "BitBusCVIn.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBus::CVIn::CVIn()
   : Svin::Module()
   , cvInput(this, Panel::CVIn)
   , inputMapper(-5.0, 5.0, 0.0, 255.0)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   registerAsBusModule<Message>();
}

BitBus::CVIn::~CVIn()
{
}

void BitBus::CVIn::process(const ProcessArgs& args)
{
   // optics
   if (!busModule<Message>(Side::Right))
   {
      busOutIndicator.setOff();
      return;
   }

   busOutIndicator.setOn();

   // sound
   Message message;
   if (cvInput.isConnected())
   {
      message.channelCount = cvInput.getNumberOfChannels();
      for (uint8_t channel = 0; channel < message.channelCount; channel++)
      {
         const float voltageInput = cvInput.getVoltage(channel); // from -5.0 V to + 5.0 V
         message.byte[channel] = static_cast<uint8_t>(inputMapper(voltageInput));
      }
   }

   sendBusMessage<Message>(Side::Right, message);
}

// widget

BitBus::CVInWidget::CVInWidget(CVIn* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusCVIn = Svin::Origin::the()->addModule<BitBus::CVIn, BitBus::CVInWidget>("BitBusCVIn");
