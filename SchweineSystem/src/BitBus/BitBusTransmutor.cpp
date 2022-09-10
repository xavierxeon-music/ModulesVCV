#include "BitBusTransmutor.h"
#include "BitBusTransmutorPanel.h"

#include <Maths.h>
#include <Sound/StandardTable.h>
#include <Tools/BoolField.h>
#include <Tools/FastRandom.h>
#include <Tools/Range.h>
#include <Tools/Variable.h>

#include <SvinOrigin.h>

// randowm walk

BitBusTransmutor::RandomWalkTables::RandomWalkTables()
   : WaveTable::StepTable(1024)
   , seed(0)
{
   const float size = 0.3;
   for (uint16_t tmpSeed = 0; tmpSeed < seedCount; tmpSeed++)
   {
      float maxValue = -1.0;
      float minValue = 1.0;
      float tmpTable[fidelity];

      FastRandom random(tmpSeed);
      float value = 0.0f;
      for (uint16_t index = 0; index < fidelity; index++)
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

      Range::Mapper mapper(minValue, maxValue, -1.0, 1.0);
      for (uint16_t index = 0; index < fidelity; index++)
      {
         const float value = mapper(tmpTable[index]);
         tables[tmpSeed][index] = value;

         if (17 == tmpSeed)
            std::cout << index << " " << value << std::endl;
      }
   }
}

float BitBusTransmutor::RandomWalkTables::valueByAngle(const float& angle) const
{
   const uint64_t fullIndex = stepIndexFromAngle(angle);

   uint8_t minor = fullIndex % fidelity;
   uint8_t major = (fullIndex - minor) / fidelity;

   const float majorValue = tables[seed][major];
   if (fidelity == major + 1)
      return majorValue;

   const float percentage = static_cast<float>(minor) / fidelity;
   const float nextValue = tables[seed][major + 1];
   const float diff = percentage * (nextValue - majorValue);

   const float value = majorValue + diff;
   return value;
}

// transmuter

BitBusTransmutor::BitBusTransmutor()
   : Svin::Module()
   , Svin::Exapnder<BitBusMessage>(this)
   , upButton(this, Panel::Seed_Up)
   , downButton(this, Panel::Seed_Down)
   , displayController(this, Panel::Text_Seed_Number)
   , busInIndicator(this, Panel::RGB_BusIn)
   , busOutIndicator(this, Panel::RGB_BusOut)
   , inputMapper(-1.0, 1.0, 0.0, 255.0)
   , tables()
{
   setup();
   displayController.setColor(Svin::Color{255, 255, 0});

   allowExpanderOnLeft();
   allowExpanderOnRight();
}

void BitBusTransmutor::load(const Svin::Json::Object& rootObject)
{
   tables.seed = rootObject.get("seed").toInt();
}

void BitBusTransmutor::save(Svin::Json::Object& rootObject)
{
   rootObject.set("seed", tables.seed);
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

   Variable::Integer<uint8_t> var(tables.seed, 0, RandomWalkTables::seedCount - 1, true);
   if (upButton.isTriggered())
      var.increment();
   else if (downButton.isTriggered())
      var.decrement();

   displayController.setText(std::to_string(tables.seed));

   const BoolField8 boolFieldIn = receiveFromLeft().byte;
   const float angle = static_cast<float>(boolFieldIn) * 2.0 * Maths::pi / 255.0;
   const float value = tables.valueByAngle(angle);

   BoolField8 boolFieldOut = static_cast<uint8_t>(inputMapper(value));
   sendToRight(BitBusMessage{boolFieldOut});
}

// widget

BitBusTransmutorWidget::BitBusTransmutorWidget(BitBusTransmutor* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusTransmutor = Svin::Origin::the()->addModule<BitBusTransmutor, BitBusTransmutorWidget>("BitBusTransmutor");
