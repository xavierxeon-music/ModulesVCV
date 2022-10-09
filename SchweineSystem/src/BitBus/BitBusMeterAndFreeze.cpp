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
   registerAsBusModule<Data>();

   lightList.append({Panel::RGB_Bit8_Status1,
                     Panel::RGB_Bit7_Status1,
                     Panel::RGB_Bit6_Status1,
                     Panel::RGB_Bit5_Status1,
                     Panel::RGB_Bit4_Status1,
                     Panel::RGB_Bit3_Status1,
                     Panel::RGB_Bit2_Status1,
                     Panel::RGB_Bit1_Status1});

   for (uint8_t index = 0; index < 8; index++)
      lightList[index]->setDefaultColor(Color(0, 255, 0));

   freezeButton.setLatchBuddy(&freezeInput);
   freezeButton.setDefaultColor(Color(0, 0, 255));
   freezeButton.setOff();

   sampleButton.setLatchBuddy(&sampleInput);
   sampleButton.setDefaultColor(Color(0, 0, 255));
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
   if (busModule<Data>(Side::Right))
      busOutIndicator.setOn();
   else
      busOutIndicator.setOff();

   if (!busModule<Data>(Side::Left))
      busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!busModule<Data>(Side::Left) && !busModule<Data>(Side::Right))
      return;

   Data data = getBusData<Data>(Side::Left);

   const bool freezeMode = freezeButton.isLatched();
   freezeButton.setActive(freezeMode);

   const bool sample = sampleButton.isLatched();
   for (uint8_t channel = 0; channel < data.channelCount; channel++)
   {
      if (!freezeMode || (freezeMode && sample))
         freezeBuffer[channel] = data.byte[channel];

      data.byte[channel] = freezeBuffer[channel];
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      const bool value = freezeBuffer[0].get(index);
      lightList[index]->setActive(value);
   }

   sendBusData<Data>(Side::Right, data);
}

// widget

BitBus::MeterAndFreezeWidget::MeterAndFreezeWidget(MeterAndFreeze* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelBitBusMeterAndFreeze = Svin::Origin::the()->addModule<BitBus::MeterAndFreeze, BitBus::MeterAndFreezeWidget>("BitBusMeterAndFreeze");
