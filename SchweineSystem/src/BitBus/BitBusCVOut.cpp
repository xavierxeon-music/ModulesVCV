#include "BitBusCVOut.h"
#include "BitBusCVOutPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystemMaster.h"

BitBusCVOut::BitBusCVOut()
   : SchweineSystem::Module()
   , SchweineSystem::Exapnder<BitBusMessage>(this)
   , outputMapper(0.0, 255.0, -5.0, 5.0)
   , busInIndicator(this, Panel::RGB_BusIn)
{
   setup();

}

BitBusCVOut::~BitBusCVOut()
{
}

void BitBusCVOut::process(const ProcessArgs& args)
{
   if (!hasExpanderToLeft())
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
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusCVOut = SchweineSystem::Master::the()->addModule<BitBusCVOut, BitBusCVOutWidget>("BitBusCVOut");
