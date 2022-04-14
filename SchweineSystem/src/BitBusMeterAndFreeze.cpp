#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include "SchweineSystem.h"

using Panel = BitBusMeterAndFreeze::Panel;

static const std::vector<Panel::LightId> lightId = {Panel::Red_Bit8, Panel::Red_Bit7, Panel::Red_Bit6, Panel::Red_Bit5, Panel::Red_Bit4, Panel::Red_Bit3, Panel::Red_Bit2, Panel::Red_Bit1};

BitBusMeterAndFreeze::BitBusMeterAndFreeze()
   : Module()
   , BitBusCommon(this)
   , averageList()
   , freezTrigger()
   , freezeMode(false)
   , sampleTrigger()
{
   setup();
}

BitBusMeterAndFreeze::~BitBusMeterAndFreeze()
{
}

void BitBusMeterAndFreeze::onAdd(const AddEvent& e)
{
   (void)e;
   registerBusInput();
   registerBusOutput();
}

void BitBusMeterAndFreeze::process(const ProcessArgs& args)
{
   if (canSendBusMessage())
      lights[Panel::Blue_BusOut].setBrightness(1.0);
   else
      lights[Panel::Blue_BusOut].setBrightness(0.0);

   BoolField8 boolField = 0;
   if (!canReceiveBusMessage())
   {
      lights[Panel::Blue_BusIn].setBrightness(0.0);
   }
   else
   {
      lights[Panel::Blue_BusIn].setBrightness(1.0);
      boolField = getByteFromBus();
   }

   bool freezeValue = params[Panel::GateFreeze].getValue();
   if (inputs[Panel::GateFreeze].isConnected())
      freezeValue = (inputs[Panel::GateFreeze].getVoltage() > 3.0);

   if (freezTrigger.process(freezeValue))
      freezeMode ^= true;
   lights[Panel::Blue_FlipFreeze].setBrightness(freezeMode);

   bool sampleValue = params[Panel::GateSample].getValue();
   if (inputs[Panel::GateSample].isConnected())
      sampleValue = (inputs[Panel::GateSample].getVoltage() > 3.0);

   const bool sample = sampleTrigger.process(sampleValue);
   if (!freezeMode || (freezeMode && sample))
      freezeBuffer = boolField;

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = freezeBuffer.get(index);
      lights[lightId.at(index) + 1].setBrightness(value ? 1.0 : 0.0);
   }

   if (canSendBusMessage())
      sendByteToBus(freezeBuffer);
}

Model* modelBitBusMeterAndFreeze = SchweineSystem::the()->addModule<BitBusMeterAndFreeze, BitBusMeterAndFreezeWidget>("BitBusMeterAndFreeze", SchweineSystem::Series::None);

