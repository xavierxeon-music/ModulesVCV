#include "BitBusCVOut.h"
#include "BitBusCVOutPanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystem.h"

BitBusCVOut::BitBusCVOut()
   : Module()
   , BitBusCommon(this)
   , outputMapper(0.0, 255.0, -5.0, 5.0)
{
   setup();
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
      lights[Panel::Blue_BusIn].setBrightness(0.0);
      outputs[Panel::CVOut].setVoltage(0.0);
      return;
   }

   lights[Panel::Blue_BusIn].setBrightness(1.0);

   BoolField8 boolField = getByteFromBus();

   const float voltageOutput = outputMapper(static_cast<float>(boolField));
   outputs[Panel::CVOut].setVoltage(voltageOutput);
}

Model* modelBitBusCVOut = SchweineSystem::the()->addModule<BitBusCVOut, BitBusCVOutWidget>("BitBusCVOut");
