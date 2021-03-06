#include "GateLatch.h"
#include "GateLatchPanel.h"

#include <SchweineSystemJson.h>
#include <SchweineSystemMaster.h>

GateLatch::GateLatch()
   : SchweineSystem::Module()
   , inputList(inputs)
   , outputList(outputs)
   , lightList(this)
   , triggers{}
   , activity{}
   , latches{false, false, false, false, false, false, false, false}
   , resetTrigger()
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

   lightList.append({Panel::RGB_Row1_Status1,
                     Panel::RGB_Row2_Status1,
                     Panel::RGB_Row3_Status1,
                     Panel::RGB_Row4_Status1,
                     Panel::RGB_Row5_Status1,
                     Panel::RGB_Row6_Status1,
                     Panel::RGB_Row7_Status1,
                     Panel::RGB_Row8_Status1});
}

void GateLatch::process(const ProcessArgs& args)
{
   bool reset = (params[Panel::Reset_Button].getValue() > 0.1);

   if (!reset && inputs[Panel::Reset_Input].isConnected() && inputs[Panel::Reset_Input].getVoltage() > 3.0)
      reset = true;

   if (resetTrigger.process(reset))
   {
      for (uint8_t index = 0; index < 8; index++)
      {
         triggers[index].reset();
         latches[index] = false;
         activity[index].reset();
         lightList[index]->setColor(SchweineSystem::Color{0, 0, 0});
      }
      return;
   }

   for (uint8_t index = 0; index < 8; index++)
   {
      const float voltage = [&]()
      {
         if (inputList[index]->isConnected())
            return inputList[index]->getVoltage();
         else if (0 == index)
            return 0.0f;
         else
            return outputList[index - 1]->getVoltage();
      }();

      const bool trigger = triggers[index].process(voltage > 3.0);
      if (trigger)
      {
         latches[index] ^= true;
         activity[index].trigger(0.1);
      }

      outputList[index]->setVoltage(latches[index] ? 10.0f : 0.0f);
      if (activity[index].process(args.sampleTime))
         lightList[index]->setColor(SchweineSystem::Color{255, 0, 255});
      else if (latches[index])
         lightList[index]->setColor(SchweineSystem::Color{255, 255, 0});
      else
         lightList[index]->setColor(SchweineSystem::Color{0, 0, 0});
   }
}

json_t* GateLatch::dataToJson()
{
   using namespace SchweineSystem::Json;

   Array latchArray;
   for (uint8_t index = 0; index < 8; index++)
   {
      latchArray.append(Value(latches[index]));
   }

   Object rootObject;
   rootObject.set("latches", latchArray);

   return rootObject.toJson();
}

void GateLatch::dataFromJson(json_t* rootJson)
{
   using namespace SchweineSystem::Json;

   Object rootObject(rootJson);
   Array latchArray = rootObject.get("latches").toArray();

   for (uint8_t index = 0; index < 8; index++)
   {
      latches[index] = latchArray.get(index).toBool();
   }
}

GateLatchWidget::GateLatchWidget(GateLatch* module)
   : SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelGateLatch = SchweineSystem::Master::the()->addModule<GateLatch, GateLatchWidget>("GateLatch");
