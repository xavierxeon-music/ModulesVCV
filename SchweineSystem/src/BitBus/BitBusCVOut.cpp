#include "BitBusCVOut.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBus::CVOut::CVOut()
   : Svin::Module()
   , cvOutput(this, Panel::CVOut)
   , outputMapper(0.0, 255.0, -5.0, 5.0)
   , busInIndicator(this, Panel::RGB_BusIn)
{
   setup();
   registerAsBusModule<Message>();
}

BitBus::CVOut::~CVOut()
{
}

void BitBus::CVOut::process(const ProcessArgs& args)
{
   // optics
   if (!busModule<Message>(Side::Left))
   {
      busInIndicator.setOff();
      cvOutput.setNumberOfChannels(1);
      cvOutput.setVoltage(0.0);
      return;
   }

   busInIndicator.setOn();

   // sound
   const Message message = getBusMessage<Message>(Side::Left);
   cvOutput.setNumberOfChannels(message.channelCount);

   for (uint8_t channel = 0; channel < message.channelCount; channel++)
   {
      const float voltageOutput = outputMapper(static_cast<float>(message.byte[channel]));
      cvOutput.setVoltage(voltageOutput, channel);
   }
}

// widget

BitBus::CVOutWidget::CVOutWidget(CVOut* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusCVOut = Svin::Origin::the()->addModule<BitBus::CVOut, BitBus::CVOutWidget>("BitBusCVOut");
