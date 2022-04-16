#include "BitBusNegate.h"
#include "BitBusNegatePanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystemMaster.h"

using Panel = BitBusNegate::Panel;

BitBusNegate::BitBusNegate()
   : Module()
   , BitBusCommon(this)
   , lightList(lights)
   , paramList(params)
   , gateList(inputs)
   , gateTrigger()
   , gates{}
{
   setup();

   lightList.append({Panel::Red_Bit8_Latch, Panel::Red_Bit7_Latch, Panel::Red_Bit6_Latch, Panel::Red_Bit5_Latch, Panel::Red_Bit4_Latch, Panel::Red_Bit3_Latch, Panel::Red_Bit2_Latch, Panel::Red_Bit1_Latch});
   for (uint8_t index = 0; index < 8; index++)
      lightList[index]->setDefaultColor({0, 0, 255});

   paramList.append({Panel::Bit8_Latch, Panel::Bit7_Latch, Panel::Bit6_Latch, Panel::Bit5_Latch, Panel::Bit4_Latch, Panel::Bit3_Latch, Panel::Bit2_Latch, Panel::Bit1_Latch});
   gateList.append({Panel::Bit8_GateIn, Panel::Bit7_GateIn, Panel::Bit6_GateIn, Panel::Bit5_GateIn, Panel::Bit4_GateIn, Panel::Bit3_GateIn, Panel::Bit2_GateIn, Panel::Bit1_GateIn});
   busInIndicator.assign(Panel::Red_BusIn);
   busOutIndicator.assign(Panel::Red_BusOut);
}

BitBusNegate::~BitBusNegate()
{
}

void BitBusNegate::onAdd(const AddEvent& e)
{
   (void)e;
   registerBusInput();
   registerBusOutput();
}

json_t* BitBusNegate::dataToJson()
{
   json_t* rootJson = json_object();
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string key = "negate" + std::to_string(index);
      json_object_set_new(rootJson, key.c_str(), json_boolean(gates[index]));
   }

   return rootJson;
}

void BitBusNegate::dataFromJson(json_t* rootJson)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string key = "negate" + std::to_string(index);
      json_t* negateJson = json_object_get(rootJson, key.c_str());

      if (!negateJson)
         continue;

      gates[index] = json_boolean_value(negateJson);
      lightList[index]->setOn();
   }
}

void BitBusNegate::process(const ProcessArgs& args)
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

   for (uint8_t index = 0; index < 8; index++)
   {
      bool negateValue = paramList[index]->getValue();
      if (gateList[index]->isConnected())
         negateValue = (gateList[index]->getVoltage() > 3.0);

      if (gateTrigger[index].process(negateValue))
         gates[index] ^= true;

      if (gates[index])
         lightList[index]->setOn();
      else
         lightList[index]->setOff();

      if (gates[index]) // negate value
      {
         bool value = boolField.get(index);
         value ^= true;
         boolField.set(index, value);
      }
   }

   if (canSendBusMessage())
      sendByteToBus(boolField);
}

Model* modelBitBusNegate = SchweineSystem::Master::the()->addModule<BitBusNegate, BitBusNegateWidget>("BitBusNegate");
