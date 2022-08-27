#include "BitBusCVOut.h"
#include "BitBusCVOutPanel.h"

#include <Tools/BoolField.h>

#include <SvinMaster.h>

BitBusCVOut::BitBusCVOut()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
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
   if (!canCommunicatWithLeft())
   {
      busInIndicator.setOff();
      outputs[Panel::CVOut].setVoltage(0.0);
      return;
   }

   busInIndicator.setOn();

   BoolField8 boolField = receiveFromLeft().byte;

   const float voltageOutput = outputMapper(static_cast<float>(boolField));
   outputs[Panel::CVOut].setVoltage(voltageOutput);
}

// widget

BitBusCVOutWidget::BitBusCVOutWidget(BitBusCVOut* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusCVOut = Svin::Master::the()->addModule<BitBusCVOut, BitBusCVOutWidget>("BitBusCVOut");
