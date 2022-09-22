#include "BitBusMeterAndFreeze.h"

#include <SvinOrigin.h>

// meter and freeze

BitBus::MeterAndFreeze::MeterAndFreeze()
   : Svin::Module()
   , lightList(this)
   , freezeButton(this, Panel::FlipFreeze, Panel::RGB_FlipFreeze)
   , freezeInput(this, Panel::GateFreeze)
   , freezeBuffer{}
   , sampleButton(this, Panel::FlipSample, Panel::RGB_FlipSample)
   , sampleInput(this, Panel::GateSample)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   registerAsBusModule<Message>();

   lightList.append({Panel::RGB_Bit8_Status1,
                     Panel::RGB_Bit7_Status1,
                     Panel::RGB_Bit6_Status1,
                     Panel::RGB_Bit5_Status1,
                     Panel::RGB_Bit4_Status1,
                     Panel::RGB_Bit3_Status1,
                     Panel::RGB_Bit2_Status1,
                     Panel::RGB_Bit1_Status1});

   for (uint8_t index = 0; index < 8; index++)
      lightList[index]->setDefaultColor(Svin::Color{0, 255, 0});

   freezeButton.setLatchBuddy(&freezeInput);
   freezeButton.setDefaultColor(Svin::Color{0, 0, 255});
   freezeButton.setOff();

   sampleButton.setLatchBuddy(&sampleInput);
   sampleButton.setDefaultColor(Svin::Color{0, 0, 255});
   sampleButton.setOff();
}

BitBus::MeterAndFreeze::~MeterAndFreeze()
{
}

void BitBus::MeterAndFreeze::load(const Svin::Json::Object& rootObject)
{
   const bool freezeMode = rootObject.get("freeze").toBool();
   freezeButton.setLatched(freezeMode);
}

void BitBus::MeterAndFreeze::save(Svin::Json::Object& rootObject)
{
   rootObject.set("freeze", freezeButton.isLatched(false));
}

void BitBus::MeterAndFreeze::process(const ProcessArgs& args)
{
   if (busModule<Message>(Side::Right))
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   if (!busModule<Message>(Side::Left))
      busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!busModule<Message>(Side::Left) && !busModule<Message>(Side::Right))
      return;

   Message message = getBusMessage<Message>(Side::Left);

   const bool freezeMode = freezeButton.isLatched();
   freezeButton.setActive(freezeMode);

   const bool sample = sampleButton.isLatched();
   for (uint8_t channel = 0; channel < message.channelCount; channel++)
   {
      if (!freezeMode || (freezeMode && sample))
         freezeBuffer[channel] = message.byte[channel];

      message.byte[channel] = freezeBuffer[channel];
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = freezeBuffer[0].get(index);
      lightList[index]->setActive(value);
   }

   sendBusMessage<Message>(Side::Right, message);
}

// widget

BitBus::MeterAndFreezeWidget::MeterAndFreezeWidget(MeterAndFreeze* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusMeterAndFreeze = Svin::Origin::the()->addModule<BitBus::MeterAndFreeze, BitBus::MeterAndFreezeWidget>("BitBusMeterAndFreeze");
