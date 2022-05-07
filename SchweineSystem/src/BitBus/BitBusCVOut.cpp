#include "BitBusCVOut.h"
#include "BitBusCVOutPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystemMaster.h"

BitBusCVOut::BitBusCVOut()
   : SchweineSystem::Module()
   , BitBusCommon(this)
   , outputMapper(0.0, 255.0, -5.0, 5.0)
{
   setup();

   busInIndicator.assign(Panel::RGB_BusIn);
}

void BitBusCVOut::onAdd(const AddEvent& e)
{
   (void)e;
   registerBusInput();
}

BitBusCVOut::~BitBusCVOut()
{
}

void BitBusCVOut::process(const ProcessArgs& args)
{
   if (!canReceiveBusMessage())
   {
      busInIndicator.setOff();
      outputs[Panel::CVOut].setVoltage(0.0);
      return;
   }

   busInIndicator.setOn();

   BoolField8 boolField = getByteFromBus();

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
