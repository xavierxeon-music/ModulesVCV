#include "TimeLordChronicle.h"
#include "TimeLordChroniclePanel.h"

#include <SchweineSystemMaster.h>

TimeLordChronicle::TimeLordChronicle()
   : SchweineSystem::Module()
   , inputList(inputs)
   , lightMeterList(this)
   , displayList(this)
   , voltageToValue(0.0, 10.0, 0, 255)
{
   setup();

   inputList.append({Panel::Channel1_Input,
                     Panel::Channel2_Input,
                     Panel::Channel3_Input,
                     Panel::Channel4_Input,
                     Panel::Channel5_Input,
                     Panel::Channel6_Input,
                     Panel::Channel7_Input,
                     Panel::Channel8_Input});

   lightMeterList.append({Panel::Value_Channel1_Strip,
                          Panel::Value_Channel2_Strip,
                          Panel::Value_Channel3_Strip,
                          Panel::Value_Channel4_Strip,
                          Panel::Value_Channel5_Strip,
                          Panel::Value_Channel6_Strip,
                          Panel::Value_Channel7_Strip,
                          Panel::Value_Channel8_Strip});

   displayList.append({{Panel::Text_Channel1_Display, Panel::RGB_Channel1_Display},
                       {Panel::Text_Channel2_Display, Panel::RGB_Channel2_Display},
                       {Panel::Text_Channel3_Display, Panel::RGB_Channel3_Display},
                       {Panel::Text_Channel4_Display, Panel::RGB_Channel4_Display},
                       {Panel::Text_Channel5_Display, Panel::RGB_Channel5_Display},
                       {Panel::Text_Channel6_Display, Panel::RGB_Channel6_Display},
                       {Panel::Text_Channel7_Display, Panel::RGB_Channel7_Display},
                       {Panel::Text_Channel8_Display, Panel::RGB_Channel8_Display}});

   for (uint8_t index = 0; index < 8; index++)
   {
      lightMeterList[index]->setMaxValue(255);
      displayList[index]->setColor(SchweineSystem::Color{255, 255, 0});
      displayList[index]->setText("ABC");
   }
}

void TimeLordChronicle::process(const ProcessArgs& args)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      if (!inputList[index]->isConnected())
      {
         displayList[index]->setText("");
         continue;
      }

      const float voltage = inputList[index]->getVoltage();
      if (voltage < 0.0)
      {
         displayList[index]->setColor(SchweineSystem::Color{255, 0, 0});
         displayList[index]->setText("0");
         continue;
      }
      const uint8_t value = voltageToValue(voltage);

      lightMeterList[index]->setValue(value);

      displayList[index]->setColor(SchweineSystem::Color{255, 255, 0});
      displayList[index]->setText(std::to_string(value));
   }
}

TimeLordChronicleWidget::TimeLordChronicleWidget(TimeLordChronicle* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelTimeLordChronicle = SchweineSystem::Master::the()->addModule<TimeLordChronicle, TimeLordChronicleWidget>("TimeLordChronicle");
