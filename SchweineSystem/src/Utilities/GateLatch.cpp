#include "GateLatch.h"

#include <SvinJson.h>
#include <SvinOrigin.h>

GateLatch::GateLatch()
   : Svin::Module()
   , inputList(this)
   , outputList(this)
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

   lightList.append({Panel::RGB_Row1_Status,
                     Panel::RGB_Row2_Status,
                     Panel::RGB_Row3_Status,
                     Panel::RGB_Row4_Status,
                     Panel::RGB_Row5_Status,
                     Panel::RGB_Row6_Status,
                     Panel::RGB_Row7_Status,
                     Panel::RGB_Row8_Status});
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
         lightList[index]->setColor(Color{0, 0, 0});
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
         else // pass output above
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
         lightList[index]->setColor(Color{255, 0, 255});
      else if (latches[index])
         lightList[index]->setColor(Color{255, 255, 0});
      else
         lightList[index]->setColor(Color{0, 0, 0});
   }
}

void GateLatch::load(const Svin::Json::Object& rootObject)
{
   Svin::Json::Array latchArray = rootObject.get("latches").toArray();
   for (uint8_t index = 0; index < 8; index++)
      latches[index] = latchArray.at(index).toBool();
}

void GateLatch::save(Svin::Json::Object& rootObject)
{
   Svin::Json::Array latchArray;
   for (uint8_t index = 0; index < 8; index++)
      latchArray.append(latches[index]);

   rootObject.set("latches", latchArray);
}

// widget

GateLatchWidget::GateLatchWidget(GateLatch* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelGateLatch = Svin::Origin::the()->addModule<GateLatch, GateLatchWidget>("GateLatch");

