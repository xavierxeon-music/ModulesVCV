#include "HalfVolt.h"
#include "HalfVoltPanel.h"

#include <SchweineSystemMaster.h>

HalfVolt::HalfVolt()
   : SchweineSystem::Module()
   , inputList(inputs)
   , outputList(outputs)
{
   setup();

   inputList.append({Panel::Row1_In,
                     Panel::Row2_In,
                     Panel::Row3_In,
                     Panel::Row4_In,
                     Panel::Row5_In,
                     Panel::Row6_In,
                     Panel::Row7_In,
                     Panel::Row8_In});

   outputList.append({Panel::Row1_Out,
                      Panel::Row2_Out,
                      Panel::Row3_Out,
                      Panel::Row4_Out,
                      Panel::Row5_Out,
                      Panel::Row6_Out,
                      Panel::Row7_Out,
                      Panel::Row8_Out});
}

void HalfVolt::process(const ProcessArgs& args)
{
   for (uint8_t index = 0; index < 8; index++)
   {
      const float voltage = inputList[index]->getVoltage();
      outputList[index]->setVoltage(0.5 * voltage);
   }
}

HalfVoltWidget::HalfVoltWidget(HalfVolt* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelHalfVolt = SchweineSystem::Master::the()->addModule<HalfVolt, HalfVoltWidget>("HalfVolt");
