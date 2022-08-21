#include "TimeLordCompanion.h"
#include "TimeLordCompanionPanel.h"

#include <SchweineSystemMaster.h>

void TimeLordCompanion::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Channel8_Silence, 0.0f, 1.0f, 0.0f, "Channel8_Silence");
   configSwitch(Panel::Channel7_Silence, 0.0f, 1.0f, 0.0f, "Channel7_Silence");
   configSwitch(Panel::Channel6_Silence, 0.0f, 1.0f, 0.0f, "Channel6_Silence");
   configSwitch(Panel::Channel5_Silence, 0.0f, 1.0f, 0.0f, "Channel5_Silence");
   configSwitch(Panel::Channel4_Silence, 0.0f, 1.0f, 0.0f, "Channel4_Silence");
   configSwitch(Panel::Channel3_Silence, 0.0f, 1.0f, 0.0f, "Channel3_Silence");
   configSwitch(Panel::Channel2_Silence, 0.0f, 1.0f, 0.0f, "Channel2_Silence");
   configSwitch(Panel::Channel1_Silence, 0.0f, 1.0f, 0.0f, "Channel1_Silence");

   configButton(Panel::Channel8_Steady, "Channel8_Steady");
   configButton(Panel::Channel7_Steady, "Channel7_Steady");
   configButton(Panel::Channel6_Steady, "Channel6_Steady");
   configButton(Panel::Channel5_Steady, "Channel5_Steady");
   configButton(Panel::Channel4_Steady, "Channel4_Steady");
   configButton(Panel::Channel3_Steady, "Channel3_Steady");
   configButton(Panel::Channel2_Steady, "Channel2_Steady");
   configButton(Panel::Channel1_Steady, "Channel1_Steady");

   configInput(Panel::Channel8_SteadyOverride, "Channel8_SteadyOverride");
   configInput(Panel::Channel7_SteadyOverride, "Channel7_SteadyOverride");
   configInput(Panel::Channel6_SteadyOverride, "Channel6_SteadyOverride");
   configInput(Panel::Channel5_SteadyOverride, "Channel5_SteadyOverride");
   configInput(Panel::Channel4_SteadyOverride, "Channel4_SteadyOverride");
   configInput(Panel::Channel3_SteadyOverride, "Channel3_SteadyOverride");
   configInput(Panel::Channel2_SteadyOverride, "Channel2_SteadyOverride");
   configInput(Panel::Channel1_SteadyOverride, "Channel1_SteadyOverride");
}

void TimeLordCompanionWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/TimeLordCompanion.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeSwitch(this, Vec(89.18, 289.03), TimeLordCompanion::Panel::Channel8_Silence);
   makeSwitch(this, Vec(89.18, 251.03), TimeLordCompanion::Panel::Channel7_Silence);
   makeSwitch(this, Vec(89.18, 213.03), TimeLordCompanion::Panel::Channel6_Silence);
   makeSwitch(this, Vec(89.18, 175.03), TimeLordCompanion::Panel::Channel5_Silence);
   makeSwitch(this, Vec(89.18, 137.03), TimeLordCompanion::Panel::Channel4_Silence);
   makeSwitch(this, Vec(89.18, 99.03), TimeLordCompanion::Panel::Channel3_Silence);
   makeSwitch(this, Vec(89.18, 61.03), TimeLordCompanion::Panel::Channel2_Silence);
   makeSwitch(this, Vec(89.18, 23.03), TimeLordCompanion::Panel::Channel1_Silence);

   makeLEDButton(this, Vec(61.60, 289.03), TimeLordCompanion::Panel::Channel8_Steady, TimeLordCompanion::Panel::RGB_Channel8_Steady);
   makeLEDButton(this, Vec(61.60, 251.03), TimeLordCompanion::Panel::Channel7_Steady, TimeLordCompanion::Panel::RGB_Channel7_Steady);
   makeLEDButton(this, Vec(61.60, 213.03), TimeLordCompanion::Panel::Channel6_Steady, TimeLordCompanion::Panel::RGB_Channel6_Steady);
   makeLEDButton(this, Vec(61.60, 175.03), TimeLordCompanion::Panel::Channel5_Steady, TimeLordCompanion::Panel::RGB_Channel5_Steady);
   makeLEDButton(this, Vec(61.60, 137.03), TimeLordCompanion::Panel::Channel4_Steady, TimeLordCompanion::Panel::RGB_Channel4_Steady);
   makeLEDButton(this, Vec(61.60, 99.03), TimeLordCompanion::Panel::Channel3_Steady, TimeLordCompanion::Panel::RGB_Channel3_Steady);
   makeLEDButton(this, Vec(61.60, 61.03), TimeLordCompanion::Panel::Channel2_Steady, TimeLordCompanion::Panel::RGB_Channel2_Steady);
   makeLEDButton(this, Vec(61.60, 23.03), TimeLordCompanion::Panel::Channel1_Steady, TimeLordCompanion::Panel::RGB_Channel1_Steady);

   makeInput(this, Vec(34.07, 289.03),  TimeLordCompanion::Panel::Channel8_SteadyOverride);
   makeInput(this, Vec(34.07, 251.03),  TimeLordCompanion::Panel::Channel7_SteadyOverride);
   makeInput(this, Vec(34.07, 213.03),  TimeLordCompanion::Panel::Channel6_SteadyOverride);
   makeInput(this, Vec(34.07, 175.03),  TimeLordCompanion::Panel::Channel5_SteadyOverride);
   makeInput(this, Vec(34.07, 137.03),  TimeLordCompanion::Panel::Channel4_SteadyOverride);
   makeInput(this, Vec(34.07, 99.03),  TimeLordCompanion::Panel::Channel3_SteadyOverride);
   makeInput(this, Vec(34.07, 61.03),  TimeLordCompanion::Panel::Channel2_SteadyOverride);
   makeInput(this, Vec(34.07, 23.03),  TimeLordCompanion::Panel::Channel1_SteadyOverride);
}

