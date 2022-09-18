#include "BitBusRandomWalk.h"

#include <Maths.h>
#include <Sound/StandardTable.h>
#include <Tools/BoolField.h>
#include <Tools/FastRandom.h>
#include <Tools/Variable.h>

#include <SvinOrigin.h>

BitBusRandomWalk::BitBusRandomWalk()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
   , mixSlider(this, Panel::Mix, Panel::RGB_Mix)
   , upButton(this, Panel::Up)
   , downButton(this, Panel::Down)
   , displayController(this, Panel::Text_Bank)
   , scanInput(this, Panel::Scan)
   , scanMapper(0.0, 10.0, 0.0, 255.0)
   , mix(0.0)
   , seed(0)
   , tables{}
{
   setup();
   displayController.setColor(Svin::Color{255, 255, 0});
   mixSlider.setDefaultColor(Svin::Color{255, 255, 0});

   allowExpanderOnLeft();
   allowExpanderOnRight();

   const float size = 0.3;
   for (uint16_t tmpSeed = 0; tmpSeed < seedCount; tmpSeed++)
   {
      float maxValue = -1.0;
      float minValue = 1.0;
      float tmpTable[256];

      FastRandom random(tmpSeed);
      float value = 0.0f;
      for (uint16_t index = 0; index < 256; index++)
      {
         const float diff = (2.0f * size * random.value()) - size;
         if (value == -1.0 && diff < 0)
            value -= diff;
         else if (value == 1.0 && diff > 0)
            value -= diff;
         else
            value += diff;

         value = Range::clamp<float>(value, -1.0, 1.0);
         if (maxValue < value)
            maxValue = value;
         if (minValue > value)
            minValue = value;

         tmpTable[index] = value;
      }

      Range::Mapper mapper(minValue, maxValue, 0.0, 255.0);
      for (uint16_t index = 0; index < 256; index++)
      {
         const uint8_t value = mapper(tmpTable[index]);
         tables[tmpSeed][index] = value;
      }
   }
}

void BitBusRandomWalk::load(const Svin::Json::Object& rootObject)
{
   seed = rootObject.get("seed").toInt();
   mix = rootObject.get("mix").toReal();
}

void BitBusRandomWalk::save(Svin::Json::Object& rootObject)
{
   rootObject.set("seed", seed);
   rootObject.set("mix", mix);
}

void BitBusRandomWalk::process(const ProcessArgs& args)
{
   if (!canCommunicatWithLeft())
      return busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!canCommunicatWithRight())
      return busOutIndicator.setOff();
   else
      busOutIndicator.setOn();

   if (scanInput.isConnected())
   {
      const float voltage = scanInput.getVoltage();
      const float fSeed = scanMapper(voltage);

      seed = static_cast<uint8_t>(fSeed);
      mix = fSeed - seed;
   }
   else
   {
      Variable::Integer<uint8_t> var(seed, 0, seedCount - 1, true);
      if (upButton.isTriggered())
         var.increment();
      else if (downButton.isTriggered())
         var.decrement();

      mix = mixSlider.getValue();
   }

   mixSlider.setBrightness(mix);
   displayController.setText(std::to_string(seed));

   BitBusMessage message = receiveFromLeft();

   for (uint8_t channel = 0; channel < message.channelCount; channel++)
   {
      const uint8_t valueIn = message.byte[channel];
      uint8_t valueOut = tables[seed][valueIn];
      if (seedCount != seed + 1)
      {
         const float valueOutA = static_cast<float>(tables[seed + 0][valueIn]);
         const float valueOutB = static_cast<float>(tables[seed + 1][valueIn]);

         const float valueMix = valueOutA + (mix * (valueOutB - valueOutA));

         valueOut = static_cast<uint8_t>(valueMix);
      }

      message.byte[channel] = valueOut;
   }

   sendToRight(message);
}

// widget

BitBusRandomWalkWidget::BitBusRandomWalkWidget(BitBusRandomWalk* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusRandomWalk = Svin::Origin::the()->addModule<BitBusRandomWalk, BitBusRandomWalkWidget>("BitBusRandomWalk");

