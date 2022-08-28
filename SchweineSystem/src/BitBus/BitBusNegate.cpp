#include "BitBusNegate.h"
#include "BitBusNegatePanel.h"

#include <Tools/BoolField.h>

#include <SvinMaster.h>

BitBusNegate::BitBusNegate()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , latchList(this)
   , gateList(this)
   , gateTrigger()
   , gates{}
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   allowExpanderOnLeft();
   allowExpanderOnRight();

   latchList.append({{Panel::Bit8_GateIn, Panel::RGB_Bit8_Latch},
                     {Panel::Bit7_Latch, Panel::RGB_Bit7_Latch},
                     {Panel::Bit6_Latch, Panel::RGB_Bit6_Latch},
                     {Panel::Bit5_Latch, Panel::RGB_Bit5_Latch},
                     {Panel::Bit4_Latch, Panel::RGB_Bit4_Latch},
                     {Panel::Bit3_Latch, Panel::RGB_Bit3_Latch},
                     {Panel::Bit2_Latch, Panel::RGB_Bit2_Latch},
                     {Panel::Bit1_Latch, Panel::RGB_Bit1_Latch}});

   for (uint8_t index = 0; index < 8; index++)
      latchList[index]->setDefaultColor({0, 0, 255});

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

void BitBusNegate::load(const Svin::Json::Object& rootObject)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string key = "negate" + std::to_string(index);
      gates[index] = rootObject.get(key).toBool();
      latchList[index]->setActive(gates[index]);
   }
}

void BitBusNegate::save(Svin::Json::Object& rootObject)
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
      busOutIndicator.setOff();
   else
      busOutIndicator.setOn();

   if (!canCommunicatWithLeft())
      busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!canCommunicatWithRight() || !canCommunicatWithLeft())
      return;

   BoolField8 boolField = receiveFromLeft().byte;

   for (uint8_t index = 0; index < 8; index++)
   {
      bool negateValue = latchList[index]->isTriggered();
      if (gateList[index]->isConnected())
         negateValue = gateList[index]->isOn();

      if (gateTrigger[index].process(negateValue))
         gates[index] ^= true;

      if (gates[index])
         latchList[index]->setOn();
      else
         latchList[index]->setOff();

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
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusNegate = Svin::Master::the()->addModule<BitBusNegate, BitBusNegateWidget>("BitBusNegate");
