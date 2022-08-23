#include "BitBusCounter.h"
#include "BitBusCounterPanel.h"

#include <Tools/BoolField.h>
#include <Tools/Variable.h>

#include <SyMaster.h>

BitBusCounter::BitBusCounter()
   : Sy::Module()
   , Sy::Exapnder<BitBusMessage>(this)
   , upTrigger()
   , downTrigger()
   , counter(0)
   , counterController(this, Panel::Text_Number, Panel::RGB_Number)
   , bitIndicatorList(this)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   allowExpanderOnRight();

   bitIndicatorList.append({Panel::RGB_Bit8_Indicator,
                            Panel::RGB_Bit7_Indicator,
                            Panel::RGB_Bit6_Indicator,
                            Panel::RGB_Bit5_Indicator,
                            Panel::RGB_Bit4_Indicator,
                            Panel::RGB_Bit3_Indicator,
                            Panel::RGB_Bit2_Indicator,
                            Panel::RGB_Bit1_Indicator});

   for (uint8_t index = 0; index < 8; index++)
   {
      bitIndicatorList[index]->setDefaultColor(Sy::Color{0, 255, 255});
   }

   counterController.setColor(Sy::Color{0, 255, 255});
}

void BitBusCounter::load(const Sy::Json::Object& rootObject)
{
   counter = rootObject.get("counter").toInt();
}

void BitBusCounter::save(Sy::Json::Object& rootObject)
{
   rootObject.set("counter", counter);
}

void BitBusCounter::process(const ProcessArgs& args)
{
   const bool resetActive = (inputs[Panel::Reset].getVoltage() > 3.0);
   if (resetActive)
   {
      counter = 0;
   }
   else
   {
      const bool upActive = (inputs[Panel::Up].getVoltage() > 3.0);
      const bool downActive = (inputs[Panel::Down].getVoltage() > 3.0);

      Variable::Integer<uint8_t> var(counter, 0, 255, true);
      if (upTrigger.process(upActive))
         var.increment();
      else if (downTrigger.process(downActive))
         var.decrement();
   }

   counterController.setText(std::to_string(counter));

   if (!canCommunicatWithRight())
   {
      busOutIndicator.setOff();
      return;
   }
   else
   {
      busOutIndicator.setOn();
   }

   BoolField8 boolField = counter;
   for (uint8_t index = 0; index < 8; index++)
      bitIndicatorList[index]->setActive(boolField.get(index));

   sendToRight(BitBusMessage{boolField});
}

// widget

BitBusCounterWidget::BitBusCounterWidget(BitBusCounter* module)
: Sy::ModuleWidget(module)
{
   setup();
}

Model* modelBitBusCounter = Sy::Master::the()->addModule<BitBusCounter, BitBusCounterWidget>("BitBusCounter");
