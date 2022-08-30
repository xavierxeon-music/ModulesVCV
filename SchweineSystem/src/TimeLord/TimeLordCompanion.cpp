#include "TimeLordCompanion.h"
#include "TimeLordCompanionPanel.h"

#include <SvinOrigin.h>

TimeLordCompanion::TimeLordCompanion()
   : Svin::Module()
   , Svin::Exapnder<BusTimeLord>(this)
   // stready
   , steadyInputList(this)
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
      steadyButtonList[rampIndex]->setDefaultColor(Svin::Color{0, 0, 255});
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
         steadyButtonList[rampIndex]->setDefaultColor(Svin::Color{0, 255, 0});
         busMessage.steady[rampIndex] = (steadyInputList[rampIndex]->getVoltage() > 3.0);
      }
      else
      {
         steadyButtonList[rampIndex]->setDefaultColor(Svin::Color{0, 0, 255});
         busMessage.steady[rampIndex] = buttonSteady[rampIndex];
      }
      steadyButtonList[rampIndex]->setActive(busMessage.steady[rampIndex]);

      busMessage.silence[rampIndex] = silenceSwitches[rampIndex]->isOn();
   }

   sendToRight(busMessage);
}

void TimeLordCompanion::load(const Svin::Json::Object& rootObject)
{
   Svin::Json::Array silenceArray = rootObject.get("silence").toArray();
   Svin::Json::Array steadyArray = rootObject.get("steady").toArray();
   for (uint8_t rampIndex = 0; rampIndex < 8; rampIndex++)
   {
      bool silence = silenceArray.get(rampIndex).toBool();
      silenceSwitches[rampIndex]->setState(silence);

      buttonSteady[rampIndex] = steadyArray.get(rampIndex).toBool();
   }
}

void TimeLordCompanion::save(Svin::Json::Object& rootObject)
{
   Svin::Json::Array silenceArray;
   Svin::Json::Array steadyArray;
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
   : Svin::ModuleWidget(module)
   , logoWidget(nullptr)
{
   setup();

   std::string logoPath = asset::plugin(Svin::Origin::the()->instance(), "res/TimeLord/TimeLordLogo.svg");

   logoWidget = new Svin::SvgImage(rack::math::Vec(0, 342.5), module, logoPath, 0.4);
   const int16_t x = box.size.x - 0.5 * logoWidget->box.size.x;
   logoWidget->box.pos.x = x;
   addChild(logoWidget);

   logoWidget->visible = false;
}

void TimeLordCompanionWidget::preDraw()
{
   TimeLordCompanion* myModule = dynamic_cast<TimeLordCompanion*>(getSchweineModule());
   if (!myModule)
      return;

   logoWidget->visible = myModule->canCommunicatWithRight();
}

Model* modelTimeLordCompanion = Svin::Origin::the()->addModule<TimeLordCompanion, TimeLordCompanionWidget>("TimeLordCompanion");
