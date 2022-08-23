#include "BitBusNegate.h"
#include "BitBusNegatePanel.h"

#include <Tools/BoolField.h>

#include "SyMaster.h"
#include "SyModule.h"

using Panel = BitBusNegate::Panel;

BitBusNegate::BitBusNegate()
   : Sy::Module()
   , Sy::Exapnder<BitBusMessage>(this)
   , lightList(this)
   , paramList(params)
   , gateList(inputs)
   , gateTrigger()
   , gates{}
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();

   lightList.append({Panel::RGB_Bit8_Latch,
                     Panel::RGB_Bit7_Latch,
                     Panel::RGB_Bit6_Latch,
                     Panel::RGB_Bit5_Latch,
                     Panel::RGB_Bit4_Latch,
                     Panel::RGB_Bit3_Latch,
                     Panel::RGB_Bit2_Latch,
                     Panel::RGB_Bit1_Latch});

   for (uint8_t index = 0; index < 8; index++)
      lightList[index]->setDefaultColor({0, 0, 255});

   paramList.append({Panel::Bit8_Latch,
                     Panel::Bit7_Latch,
                     Panel::Bit6_Latch,
                     Panel::Bit5_Latch,
                     Panel::Bit4_Latch,
                     Panel::Bit3_Latch,
                     Panel::Bit2_Latch,
                     Panel::Bit1_Latch});

   gateList.append({Panel::Bit8_GateIn,
                    Panel::Bit7_GateIn,
                    Panel::Bit6_GateIn,
                    Panel::Bit5_GateIn,
                    Panel::Bit4_GateIn,
                    Panel::Bit3_GateIn,
                    Panel::Bit2_GateIn,
                    Panel::Bit1_GateIn});
}

BitBusNegate::~BitBusNegate()
{
}

void BitBusNegate::load(const Sy::Json::Object& rootObject)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string key = "negate" + std::to_string(index);
      gates[index] = rootObject.get(key).toBool();
      lightList[index]->setActive(gates[index]);
   }
}

void BitBusNegate::save(Sy::Json::Object& rootObject)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string key = "negate" + std::to_string(index);
      rootObject.set(key, gates[index]);
   }
}

void BitBusNegate::process(const ProcessArgs& args)
{
   if (!canCommunicatWithRight())
      return busOutIndicator.setOff();
   else
      busOutIndicator.setOn();

   if (!canCommunicatWithLeft())
      return busInIndicator.setOff();
   else
      busInIndicator.setOn();

   BoolField8 boolField = receiveFromLeft().byte;

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

   sendToRight(BitBusMessage{boolField});
}

// widget

BitBusNegateWidget::BitBusNegateWidget(BitBusNegate* module)
   : Sy::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusNegate = Sy::Master::the()->addModule<BitBusNegate, BitBusNegateWidget>("BitBusNegate");
