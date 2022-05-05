#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <SchweineSystemMaster.h>

void TimeLord::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Bank_Up, "Bank_Up");
   configButton(Panel::Mode, "Mode");

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");

   configOutput(Panel::Channel8_Output, "Channel8_Output");
   configOutput(Panel::Channel7_Output, "Channel7_Output");
   configOutput(Panel::Channel6_Output, "Channel6_Output");
   configOutput(Panel::Channel5_Output, "Channel5_Output");
   configOutput(Panel::Channel4_Output, "Channel4_Output");
   configOutput(Panel::Channel3_Output, "Channel3_Output");
   configOutput(Panel::Channel2_Output, "Channel2_Output");
   configOutput(Panel::Channel1_Output, "Channel1_Output");

   configPixels(Panel::Pixels_Display, 128, 64, "Display");

   configMeter(Panel::Value_Channel8_Strip, "Channel8_Strip");
   configMeter(Panel::Value_Channel7_Strip, "Channel7_Strip");
   configMeter(Panel::Value_Channel6_Strip, "Channel6_Strip");
   configMeter(Panel::Value_Channel5_Strip, "Channel5_Strip");
   configMeter(Panel::Value_Channel4_Strip, "Channel4_Strip");
   configMeter(Panel::Value_Channel3_Strip, "Channel3_Strip");
   configMeter(Panel::Value_Channel2_Strip, "Channel2_Strip");
   configMeter(Panel::Value_Channel1_Strip, "Channel1_Strip");
}

void TimeLordWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/TimeLord.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(119.58, 304.71), TimeLord::Panel::Bank_Up);
   makeButton(this, Vec(55.38, 305.58), TimeLord::Panel::Mode);

   makeInput(this, Vec(120.15, 344.83),  TimeLord::Panel::Reset);
   makeInput(this, Vec(55.15, 344.83),  TimeLord::Panel::Clock);

   makeOutput(this, Vec(117.41, 164.83), TimeLord::Panel::Channel8_Output);
   makeOutput(this, Vec(52.41, 164.83), TimeLord::Panel::Channel7_Output);
   makeOutput(this, Vec(117.41, 126.26), TimeLord::Panel::Channel6_Output);
   makeOutput(this, Vec(52.41, 126.26), TimeLord::Panel::Channel5_Output);
   makeOutput(this, Vec(117.41, 87.69), TimeLord::Panel::Channel4_Output);
   makeOutput(this, Vec(52.41, 87.69), TimeLord::Panel::Channel3_Output);
   makeOutput(this, Vec(117.41, 49.12), TimeLord::Panel::Channel2_Output);
   makeOutput(this, Vec(52.41, 49.12), TimeLord::Panel::Channel1_Output);

   makeDisplay(this, Vec(10.00, 222.19), TimeLord::Panel::Pixels_Display, 128, 64);

   makeMeter(this, Vec(92.29, 151.83), 5, TimeLord::Panel::Value_Channel8_Strip);
   makeMeter(this, Vec(27.29, 151.83), 5, TimeLord::Panel::Value_Channel7_Strip);
   makeMeter(this, Vec(92.29, 113.26), 5, TimeLord::Panel::Value_Channel6_Strip);
   makeMeter(this, Vec(27.29, 113.26), 5, TimeLord::Panel::Value_Channel5_Strip);
   makeMeter(this, Vec(92.29, 74.69), 5, TimeLord::Panel::Value_Channel4_Strip);
   makeMeter(this, Vec(27.29, 74.69), 5, TimeLord::Panel::Value_Channel3_Strip);
   makeMeter(this, Vec(92.29, 36.12), 5, TimeLord::Panel::Value_Channel2_Strip);
   makeMeter(this, Vec(27.29, 36.12), 5, TimeLord::Panel::Value_Channel1_Strip);
}

