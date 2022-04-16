#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include "SchweineSystemMaster.h"

using Panel = BitBusMeterAndFreeze::Panel;

static const std::vector<Panel::LightId> lightId = {Panel::Red_Bit8_Status1, Panel::Red_Bit7_Status1, Panel::Red_Bit6_Status1, Panel::Red_Bit5_Status1, Panel::Red_Bit4_Status1, Panel::Red_Bit3_Status1, Panel::Red_Bit2_Status1, Panel::Red_Bit1_Status1};

BitBusMeterAndFreeze::BitBusMeterAndFreeze()
   : Module()
   , BitBusCommon(this)
   , averageList()
   , freezTrigger()
   , freezeMode(false)
   , sampleTrigger()
{
   setup();

   busInIndicator.assign(Panel::Red_BusIn);
   busOutIndicator.assign(Panel::Red_BusOut);
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

json_t* BitBusMeterAndFreeze::dataToJson()
{
   json_t* rootJson = json_object();
   json_object_set_new(rootJson, "freeze", json_boolean(freezeMode));

   return rootJson;
}

void BitBusMeterAndFreeze::dataFromJson(json_t* rootJson)
{
   json_t* freezeJson = json_object_get(rootJson, "freeze");
   if (freezeJson)
   {
      freezeMode = json_boolean_value(freezeJson);
      lights[Panel::Blue_FlipFreeze].setBrightness(freezeMode);
   }
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

Model* modelBitBusMeterAndFreeze = SchweineSystem::Master::the()->addModule<BitBusMeterAndFreeze, BitBusMeterAndFreezeWidget>("BitBusMeterAndFreeze");
