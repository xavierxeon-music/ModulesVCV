#include "BitBusMeterAndFreeze.h"

#include <SvinOrigin.h>

// meter and freeze

BitBusMeterAndFreeze::BitBusMeterAndFreeze()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
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
   allowExpanderOnLeft();
   allowExpanderOnRight();

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

BitBusMeterAndFreeze::~BitBusMeterAndFreeze()
{
}

void BitBusMeterAndFreeze::load(const Svin::Json::Object& rootObject)
{
   const bool freezeMode = rootObject.get("freeze").toBool();
   freezeButton.setLatched(freezeMode);
}

void BitBusMeterAndFreeze::save(Svin::Json::Object& rootObject)
{
   rootObject.set("freeze", freezeButton.isLatched(false));
}

void BitBusMeterAndFreeze::process(const ProcessArgs& args)
{
   if (canCommunicatWithRight())
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   if (!canCommunicatWithLeft())
      busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!canCommunicatWithLeft() && !canCommunicatWithRight())
      return;

   BitBusMessage message = receiveFromLeft();

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

   sendToRight(message);
}

// widget

BitBusMeterAndFreezeWidget::BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusMeterAndFreeze = Svin::Origin::the()->addModule<BitBusMeterAndFreeze, BitBusMeterAndFreezeWidget>("BitBusMeterAndFreeze");

