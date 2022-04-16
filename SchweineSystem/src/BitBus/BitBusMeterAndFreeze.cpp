#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include "SchweineSystemMaster.h"

// average

BitBusMeterAndFreeze::Average::Average()
   : buffer()
   , sum(0)
{
}

uint16_t BitBusMeterAndFreeze::Average::observe(const bool value)
{
   const bool oldValue = buffer.add(value);

   if (value)
      sum += 1;

   if (0 < sum && oldValue)
      sum -= 1;

   return sum;
}

// meter and freeze

BitBusMeterAndFreeze::BitBusMeterAndFreeze()
   : Module()
   , BitBusCommon(this)
   , averageList()
   , lightMeterList(lights)
   , freezTrigger()
   , freezeMode(false)
   , sampleTrigger()
{
   setup();

   lightMeterList.append({{Panel::Red_Bit8_Status1, Panel::Red_Bit8_Status2, Panel::Red_Bit8_Status3, Panel::Red_Bit8_Status4, Panel::Red_Bit8_Status5},
                          {Panel::Red_Bit7_Status1, Panel::Red_Bit7_Status2, Panel::Red_Bit7_Status3, Panel::Red_Bit7_Status4, Panel::Red_Bit7_Status5},
                          {Panel::Red_Bit6_Status1, Panel::Red_Bit6_Status2, Panel::Red_Bit6_Status3, Panel::Red_Bit6_Status4, Panel::Red_Bit6_Status5},
                          {Panel::Red_Bit5_Status1, Panel::Red_Bit5_Status2, Panel::Red_Bit5_Status3, Panel::Red_Bit5_Status4, Panel::Red_Bit5_Status5},
                          {Panel::Red_Bit4_Status1, Panel::Red_Bit4_Status2, Panel::Red_Bit4_Status3, Panel::Red_Bit4_Status4, Panel::Red_Bit4_Status5},
                          {Panel::Red_Bit3_Status1, Panel::Red_Bit3_Status2, Panel::Red_Bit3_Status3, Panel::Red_Bit3_Status4, Panel::Red_Bit3_Status5},
                          {Panel::Red_Bit2_Status1, Panel::Red_Bit2_Status2, Panel::Red_Bit2_Status3, Panel::Red_Bit2_Status4, Panel::Red_Bit2_Status5},
                          {Panel::Red_Bit1_Status1, Panel::Red_Bit1_Status2, Panel::Red_Bit1_Status3, Panel::Red_Bit1_Status4, Panel::Red_Bit1_Status5}});
   for (uint8_t index = 0; index < 8; index++)
      lightMeterList[index]->setMaxValue(AverageBufferSize);

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
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   BoolField8 boolField = 0;
   if (!canReceiveBusMessage())
   {
      busInIndicator.setOff();
   }
   else
   {
      busInIndicator.setOn();
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
      const uint16_t sum = averageList[index].observe(value);

      lightMeterList[index]->setMeter(sum);
   }

   if (canSendBusMessage())
      sendByteToBus(freezeBuffer);
}

Model* modelBitBusMeterAndFreeze = SchweineSystem::Master::the()->addModule<BitBusMeterAndFreeze, BitBusMeterAndFreezeWidget>("BitBusMeterAndFreeze");