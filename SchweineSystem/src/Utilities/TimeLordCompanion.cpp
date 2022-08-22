#include "TimeLordCompanion.h"
#include "TimeLordCompanionPanel.h"

#include <SyMaster.h>

TimeLordCompanion::TimeLordCompanion()
   : Sy::Module()
   , Sy::Exapnder<BusTimeLord>(this)
   // stready
   , steadyInputList(inputs)
   , steadyButtonList(this)
   , buttonSteady{false, false, false, false, false, false, false, false}
   // silence
   , silenceSwitches(this)

{
   setup();
   allowExpanderOnRight();

   steadyInputList.append({Panel::Channel1_SteadyOverride,
                           Panel::Channel2_SteadyOverride,
                           Panel::Channel3_SteadyOverride,
                           Panel::Channel4_SteadyOverride,
                           Panel::Channel5_SteadyOverride,
                           Panel::Channel6_SteadyOverride,
                           Panel::Channel7_SteadyOverride,
                           Panel::Channel8_SteadyOverride});

   steadyButtonList.append({{Panel::Channel1_Steady, Panel::RGB_Channel1_Steady},
                            {Panel::Channel2_Steady, Panel::RGB_Channel2_Steady},
                            {Panel::Channel3_Steady, Panel::RGB_Channel3_Steady},
                            {Panel::Channel4_Steady, Panel::RGB_Channel4_Steady},
                            {Panel::Channel5_Steady, Panel::RGB_Channel5_Steady},
                            {Panel::Channel6_Steady, Panel::RGB_Channel6_Steady},
                            {Panel::Channel7_Steady, Panel::RGB_Channel7_Steady},
                            {Panel::Channel8_Steady, Panel::RGB_Channel8_Steady}});

   silenceSwitches.append({Panel::Channel1_Silence,
                           Panel::Channel2_Silence,
                           Panel::Channel3_Silence,
                           Panel::Channel4_Silence,
                           Panel::Channel5_Silence,
                           Panel::Channel6_Silence,
                           Panel::Channel7_Silence,
                           Panel::Channel8_Silence});

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      silenceSwitches[rampIndex]->setState(true);
      steadyButtonList[rampIndex]->setDefaultColor(Sy::Color{0, 0, 255});
   }
}

void TimeLordCompanion::process(const ProcessArgs& args)
{
   BusTimeLord busMessage;

   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      if (steadyButtonList[rampIndex]->isTriggered())
         buttonSteady[rampIndex] ^= true;

      if (steadyInputList[rampIndex]->isConnected())
      {
         steadyButtonList[rampIndex]->setDefaultColor(Sy::Color{0, 255, 0});
         busMessage.steady[rampIndex] = (steadyInputList[rampIndex]->getVoltage() > 3.0);
      }
      else
      {
         steadyButtonList[rampIndex]->setDefaultColor(Sy::Color{0, 0, 255});
         busMessage.steady[rampIndex] = buttonSteady[rampIndex];
      }
      steadyButtonList[rampIndex]->setActive(busMessage.steady[rampIndex]);

      busMessage.silence[rampIndex] = silenceSwitches[rampIndex]->isOn();
   }

   sendToRight(busMessage);
}

void TimeLordCompanion::load(const Sy::Json::Object& rootObject)
{
   Sy::Json::Array silenceArray = rootObject.get("silence").toArray();
   Sy::Json::Array steadyArray = rootObject.get("steady").toArray();
   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      bool silence = silenceArray.get(rampIndex).toBool();
      silenceSwitches[rampIndex]->setState(silence);

      buttonSteady[rampIndex] = steadyArray.get(rampIndex).toBool();
   }
}

void TimeLordCompanion::save(Sy::Json::Object& rootObject)
{
   Sy::Json::Array silenceArray;
   Sy::Json::Array steadyArray;
   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      const bool silence = silenceSwitches[rampIndex]->isOn();
      silenceArray.append(silence);

      steadyArray.append(buttonSteady[rampIndex]);
   }

   rootObject.set("silence", silenceArray);
   rootObject.set("steady", steadyArray);
}

// widget

TimeLordCompanionWidget::TimeLordCompanionWidget(TimeLordCompanion* module)
: Sy::ModuleWidget(module)
{
   setup();
}

Model* modelTimeLordCompanion = Sy::Master::the()->addModule<TimeLordCompanion, TimeLordCompanionWidget>("TimeLordCompanion");
