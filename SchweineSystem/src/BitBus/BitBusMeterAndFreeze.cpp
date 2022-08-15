#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include "SchweineSystemMaster.h"

// meter and freeze

BitBusMeterAndFreeze::BitBusMeterAndFreeze()
   : SchweineSystem::Module()
   , SchweineSystem::Exapnder<BitBusMessage>(this)
   , lightList(this)
   , freezTrigger()
   , freezeMode(false)
   , sampleTrigger()
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();

   lightList.append({Panel::RGB_Bit8_Status1,
                     Panel::RGB_Bit7_Status1,
                     Panel::RGB_Bit6_Status1,
                     Panel::RGB_Bit5_Status1,
                     Panel::RGB_Bit4_Status1,
                     Panel::RGB_Bit3_Status1,
                     Panel::RGB_Bit2_Status1,
                     Panel::RGB_Bit1_Status1});

   for (uint8_t index = 0; index < 8; index++)
      lightList[index]->setDefaultColor(SchweineSystem::Color{0, 255, 0});

}

BitBusMeterAndFreeze::~BitBusMeterAndFreeze()
{
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
      lights[Panel::RGB_FlipFreeze + 2].setBrightness(freezeMode);
   }
}

void BitBusMeterAndFreeze::process(const ProcessArgs& args)
{
   if (hasExpanderToRight())
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   BoolField8 boolField = 0;
   if (!hasExpanderToLeft())
   {
      busInIndicator.setOff();
   }
   else
   {
      busInIndicator.setOn();
      boolField = receiveFromLeft().byte;
   }

   bool freezeValue = params[Panel::GateFreeze].getValue();
   if (inputs[Panel::GateFreeze].isConnected())
      freezeValue = (inputs[Panel::GateFreeze].getVoltage() > 3.0);

   if (freezTrigger.process(freezeValue))
      freezeMode ^= true;
   lights[Panel::RGB_FlipFreeze + 2].setBrightness(freezeMode);

   bool sampleValue = params[Panel::GateSample].getValue();
   if (inputs[Panel::GateSample].isConnected())
      sampleValue = (inputs[Panel::GateSample].getVoltage() > 3.0);

   const bool sample = sampleTrigger.process(sampleValue);
   if (!freezeMode || (freezeMode && sample))
      freezeBuffer = boolField;

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = freezeBuffer.get(index);
      if (value)
         lightList[index]->setOn();
      else
         lightList[index]->setOff();
   }

   if (hasExpanderToRight())
      sendToRight(BitBusMessage{freezeBuffer});
}

BitBusMeterAndFreezeWidget::BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusMeterAndFreeze = SchweineSystem::Master::the()->addModule<BitBusMeterAndFreeze, BitBusMeterAndFreezeWidget>("BitBusMeterAndFreeze");
