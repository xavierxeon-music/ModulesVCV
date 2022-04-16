#include "BitBusNegate.h"
#include "BitBusNegatePanel.h"

#include <Tools/BoolField.h>

#include "SchweineSystem.h"

using Panel = BitBusNegate::Panel;

static const std::vector<Panel::LightId> lightId = {Panel::Red_Bit8_Latch, Panel::Red_Bit7_Latch, Panel::Red_Bit6_Latch, Panel::Red_Bit5_Latch, Panel::Red_Bit4_Latch, Panel::Red_Bit3_Latch, Panel::Red_Bit2_Latch, Panel::Red_Bit1_Latch};
static const std::vector<Panel::InputId> gateId = {Panel::Bit8_GateIn, Panel::Bit7_GateIn, Panel::Bit6_GateIn, Panel::Bit5_GateIn, Panel::Bit4_GateIn, Panel::Bit3_GateIn, Panel::Bit2_GateIn, Panel::Bit1_GateIn};

BitBusNegate::BitBusNegate()
   : Module()
   , BitBusCommon(this)
   , gateTrigger()
   , gates{}
{
   setup();
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
      lights[lightId.at(index) + 2].setBrightness(gates[index]);
   }
}

void BitBusNegate::process(const ProcessArgs& args)
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

   for (uint8_t index = 0; index < 8; index++)
   {
      bool negateValue = params[gateId.at(index)].getValue();
      if (inputs[gateId.at(index)].isConnected())
         negateValue = (inputs[gateId.at(index)].getVoltage() > 3.0);

      if (gateTrigger[index].process(negateValue))
         gates[index] ^= true;
      lights[lightId.at(index) + 2].setBrightness(gates[index]);

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

Model* modelBitBusNegate = SchweineSystem::the()->addModule<BitBusNegate, BitBusNegateWidget>("BitBusNegate");
