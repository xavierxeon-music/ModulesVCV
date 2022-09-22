#include "BitBusCounter.h"

#include <Tools/BoolField.h>
#include <Tools/Variable.h>

#include <SvinOrigin.h>

BitBus::Counter::Counter()
   : Svin::Module()
   , upInput(this, Panel::Up)
   , downInput(this, Panel::Down)
   , resetInput(this, Panel::Reset)
   , thresholdSlider(this, Panel::Threshold, Panel::RGB_Threshold)
   , counter(0)
   , counterController(this, Panel::Text_Number)
   , bitIndicatorList(this)
   , busOutIndicator(this, Panel::RGB_BusOut)
{
   setup();
   registerAsBusModule<Message>();

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
      bitIndicatorList[index]->setDefaultColor(Svin::Color{0, 255, 255});
   }

   counterController.setColor(Svin::Color{0, 255, 255});
   thresholdSlider.setOff();
   thresholdSlider.setRange(1.0, 10.0);
   thresholdSlider.setValue(3.0);
}

void BitBus::Counter::load(const Svin::Json::Object& rootObject)
{
   counter = rootObject.get("counter").toInt();

   const float threshold = rootObject.get("threshold").toReal();
   thresholdSlider.setValue(threshold);
}

void BitBus::Counter::save(Svin::Json::Object& rootObject)
{
   rootObject.set("counter", counter);

   const float threshold = thresholdSlider.getValue();
   rootObject.set("threshold", threshold);
}

void BitBus::Counter::process(const ProcessArgs& args)
{
   const float threshold = thresholdSlider.getValue();
   upInput.setTriggerThreshold(threshold);
   downInput.setTriggerThreshold(threshold);

   if (resetInput.isTriggered())
   {
      counter = 0;
   }
   else
   {
      Variable::Integer<uint8_t> var(counter, 0, 255, true);
      if (upInput.isTriggered())
         var.increment();
      else if (downInput.isTriggered())
         var.decrement();
   }

   counterController.setText(std::to_string(counter));

   if (!busModule<Message>(Side::Right))
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

   Message message;
   message.byte[0] = counter;

   sendBusMessage<Message>(Side::Right, message);
}

// widget

BitBus::CounterWidget::CounterWidget(Counter* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelBitBusCounter = Svin::Origin::the()->addModule<BitBus::Counter, BitBus::CounterWidget>("BitBusCounter");
