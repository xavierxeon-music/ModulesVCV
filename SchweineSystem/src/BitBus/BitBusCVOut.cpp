#include "BitBusCVOut.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBusCVOut::BitBusCVOut()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , cvOutput(this, Panel::CVOut)
   , outputMapper(0.0, 255.0, -5.0, 5.0)
   , busInIndicator(this, Panel::RGB_BusIn)
{
   setup();
   allowExpanderOnLeft();
}

BitBusCVOut::~BitBusCVOut()
{
}

void BitBusCVOut::process(const ProcessArgs& args)
{
   // optics
   if (!canCommunicatWithLeft())
   {
      busInIndicator.setOff();
      cvOutput.setNumberOfChannels(1);
      cvOutput.setVoltage(0.0);
      return;
   }

   busInIndicator.setOn();

   // sound
   const BitBusMessage message = receiveFromLeft();
   cvOutput.setNumberOfChannels(message.channelCount);

   for (uint8_t channel = 0; channel < message.channelCount; channel++)
   {
      const float voltageOutput = outputMapper(static_cast<float>(message.byte[channel]));
      cvOutput.setVoltage(voltageOutput, channel);
   }
}

// widget

BitBusCVOutWidget::BitBusCVOutWidget(BitBusCVOut* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusCVOut = Svin::Origin::the()->addModule<BitBusCVOut, BitBusCVOutWidget>("BitBusCVOut");

