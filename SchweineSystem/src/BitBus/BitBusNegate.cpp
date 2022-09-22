#include "BitBusNegate.h"

#include <Tools/BoolField.h>

#include <SvinOrigin.h>

BitBus::Negate::Negate()
   : Svin::Module()
   , latchList(this)
   , gateList(this)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   registerAsBusModule<Message>();

   latchList.append({{Panel::Bit8_GateIn, Panel::RGB_Bit8_Latch},
                     {Panel::Bit7_Latch, Panel::RGB_Bit7_Latch},
                     {Panel::Bit6_Latch, Panel::RGB_Bit6_Latch},
                     {Panel::Bit5_Latch, Panel::RGB_Bit5_Latch},
                     {Panel::Bit4_Latch, Panel::RGB_Bit4_Latch},
                     {Panel::Bit3_Latch, Panel::RGB_Bit3_Latch},
                     {Panel::Bit2_Latch, Panel::RGB_Bit2_Latch},
                     {Panel::Bit1_Latch, Panel::RGB_Bit1_Latch}});

   gateList.append({Panel::Bit8_GateIn,
                    Panel::Bit7_GateIn,
                    Panel::Bit6_GateIn,
                    Panel::Bit5_GateIn,
                    Panel::Bit4_GateIn,
                    Panel::Bit3_GateIn,
                    Panel::Bit2_GateIn,
                    Panel::Bit1_GateIn});

   for (uint8_t index = 0; index < 8; index++)
   {
      latchList[index]->setDefaultColor({0, 0, 255});
      latchList[index]->setLatchBuddy(gateList[index]);
   }
}

BitBus::Negate::~Negate()
{
}

void BitBus::Negate::load(const Svin::Json::Object& rootObject)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string key = "negate" + std::to_string(index);
      const bool active = rootObject.get(key).toBool();
      latchList[index]->setLatched(active);
   }
}

void BitBus::Negate::save(Svin::Json::Object& rootObject)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const std::string key = "negate" + std::to_string(index);
      rootObject.set(key, latchList[index]->isLatched(false));
   }
}

void BitBus::Negate::process(const ProcessArgs& args)
{
   if (!busModule<Message>(Side::Right))
      busOutIndicator.setOff();
   else
      busOutIndicator.setOn();

   if (!busModule<Message>(Side::Left))
      busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!busModule<Message>(Side::Right) || !busModule<Message>(Side::Left))
      return;

   Message message = getBusMessage<Message>(Side::Left);

   for (uint8_t channel = 0; channel < message.channelCount; channel++)
   {
      BoolField8 boolField = message.byte[channel];
      for (uint8_t index = 0; index < 8; index++)
      {
         const bool active = latchList[index]->isLatched();
         latchList[index]->setActive(active);

         if (active) // negate value
            boolField.flip(index);
      }
      message.byte[channel] = boolField;
   }

   sendBusMessage<Message>(Side::Right, message);
}

// widget

BitBus::NegateWidget::NegateWidget(Negate* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusNegate = Svin::Origin::the()->addModule<BitBus::Negate, BitBus::NegateWidget>("BitBusNegate");
