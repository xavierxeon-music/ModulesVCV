#include "BitBusTransmutor.h"
#include "BitBusTransmutorPanel.h"

#include <Maths.h>
#include <Sound/StandardTable.h>
#include <Tools/BoolField.h>
#include <Tools/FastRandom.h>
#include <Tools/Range.h>
#include <Tools/Variable.h>

#include <SvinOrigin.h>

BitBusTransmutor::BitBusTransmutor()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , upButton(this, Panel::Seed_Up)
   , downButton(this, Panel::Seed_Down)
   , displayController(this, Panel::Text_Seed_Number)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
   , seed(0)
   , tables{}
{
   setup();
   displayController.setColor(Svin::Color{255, 255, 0});

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

void BitBusTransmutor::load(const Svin::Json::Object& rootObject)
{
   seed = rootObject.get("seed").toInt();
}

void BitBusTransmutor::save(Svin::Json::Object& rootObject)
{
   rootObject.set("seed", seed);
}

void BitBusTransmutor::process(const ProcessArgs& args)
{
   if (!canCommunicatWithLeft())
      return busInIndicator.setOff();
   else
      busInIndicator.setOn();

   if (!canCommunicatWithRight())
      return busOutIndicator.setOff();
   else
      busOutIndicator.setOn();

   Variable::Integer<uint8_t> var(seed, 0, seedCount - 1, true);
   if (upButton.isTriggered())
      var.increment();
   else if (downButton.isTriggered())
      var.decrement();

   displayController.setText(std::to_string(seed));

   const uint8_t valueIn = receiveFromLeft().byte;
   const uint8_t valueOut = tables[seed][valueIn];

   sendToRight(BitBusMessage{valueOut});
}

// widget

BitBusTransmutorWidget::BitBusTransmutorWidget(BitBusTransmutor* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusTransmutor = Svin::Origin::the()->addModule<BitBusTransmutor, BitBusTransmutorWidget>("BitBusTransmutor");
