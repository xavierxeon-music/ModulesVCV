#include "BitBusCVOut.h"
#include "BitBusCVOutPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystemMaster.h"

BitBusCVOut::BitBusCVOut()
   : Module()
   , BitBusCommon(this)
   , outputMapper(0.0, 255.0, -5.0, 5.0)
{
   setup();

   busInIndicator.assign(Panel::Red_BusIn);
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

Model* modelBitBusCVOut = SchweineSystem::Master::the()->addModule<BitBusCVOut, BitBusCVOutWidget>("BitBusCVOut");
