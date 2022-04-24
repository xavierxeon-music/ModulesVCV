#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void TimeLord::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Mode, "Mode");
   configButton(Panel::Bank_Up, "Bank_Up");

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

   configDisplay(Panel::Text_Bank_Display, "Bank_Display");
   configDisplay(Panel::Text_Channel8_Display, "Channel8_Display");
   configDisplay(Panel::Text_Channel7_Display, "Channel7_Display");
   configDisplay(Panel::Text_Channel6_Display, "Channel6_Display");
   configDisplay(Panel::Text_Channel5_Display, "Channel5_Display");
   configDisplay(Panel::Text_Channel4_Display, "Channel4_Display");
   configDisplay(Panel::Text_Channel3_Display, "Channel3_Display");
   configDisplay(Panel::Text_Channel2_Display, "Channel2_Display");
   configDisplay(Panel::Text_Channel1_Display, "Channel1_Display");

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

   makeButton(this, Vec(38.70, 247.47), TimeLord::Panel::Mode, TimeLord::Panel::RGB_Mode);
   makeButton(this, Vec(38.23, 117.31), TimeLord::Panel::Bank_Up, TimeLord::Panel::RGB_Bank_Up);

   makeInput(this, Vec(38.69, 344.74),  TimeLord::Panel::Reset);
   makeInput(this, Vec(38.69, 298.64),  TimeLord::Panel::Clock);

   makeOutput(this, Vec(155.83, 336.72), TimeLord::Panel::Channel8_Output);
   makeOutput(this, Vec(155.83, 292.07), TimeLord::Panel::Channel7_Output);
   makeOutput(this, Vec(155.00, 247.42), TimeLord::Panel::Channel6_Output);
   makeOutput(this, Vec(155.00, 202.77), TimeLord::Panel::Channel5_Output);
   makeOutput(this, Vec(155.00, 158.12), TimeLord::Panel::Channel4_Output);
   makeOutput(this, Vec(155.00, 113.47), TimeLord::Panel::Channel3_Output);
   makeOutput(this, Vec(155.83, 68.82), TimeLord::Panel::Channel2_Output);
   makeOutput(this, Vec(155.00, 24.17), TimeLord::Panel::Channel1_Output);

   makeLight(this, Vec(39.15, 225.19), TimeLord::Panel::RGB_Current);
   makeLight(this, Vec(39.15, 201.58), TimeLord::Panel::RGB_Count);
   makeLight(this, Vec(38.99, 177.46), TimeLord::Panel::RGB_Length);
   makeLight(this, Vec(38.99, 153.34), TimeLord::Panel::RGB_Division);

   makeDisplay(this, Vec(29.23, 79.79), 1, TimeLord::Panel::Text_Bank_Display, TimeLord::Panel::RGB_Bank_Display);
   makeDisplay(this, Vec(88.15, 326.89), 3, TimeLord::Panel::Text_Channel8_Display, TimeLord::Panel::RGB_Channel8_Display);
   makeDisplay(this, Vec(88.15, 282.24), 3, TimeLord::Panel::Text_Channel7_Display, TimeLord::Panel::RGB_Channel7_Display);
   makeDisplay(this, Vec(87.32, 237.59), 3, TimeLord::Panel::Text_Channel6_Display, TimeLord::Panel::RGB_Channel6_Display);
   makeDisplay(this, Vec(87.32, 192.94), 3, TimeLord::Panel::Text_Channel5_Display, TimeLord::Panel::RGB_Channel5_Display);
   makeDisplay(this, Vec(87.32, 148.30), 3, TimeLord::Panel::Text_Channel4_Display, TimeLord::Panel::RGB_Channel4_Display);
   makeDisplay(this, Vec(87.32, 103.65), 3, TimeLord::Panel::Text_Channel3_Display, TimeLord::Panel::RGB_Channel3_Display);
   makeDisplay(this, Vec(88.15, 59.00), 3, TimeLord::Panel::Text_Channel2_Display, TimeLord::Panel::RGB_Channel2_Display);
   makeDisplay(this, Vec(87.32, 14.35), 3, TimeLord::Panel::Text_Channel1_Display, TimeLord::Panel::RGB_Channel1_Display);

   makeMeter(this, Vec(142.83, 352.32), 5, TimeLord::Panel::Value_Channel8_Strip);
   makeMeter(this, Vec(142.83, 307.67), 5, TimeLord::Panel::Value_Channel7_Strip);
   makeMeter(this, Vec(142.00, 263.02), 5, TimeLord::Panel::Value_Channel6_Strip);
   makeMeter(this, Vec(142.00, 218.37), 5, TimeLord::Panel::Value_Channel5_Strip);
   makeMeter(this, Vec(142.00, 173.72), 5, TimeLord::Panel::Value_Channel4_Strip);
   makeMeter(this, Vec(142.00, 129.07), 5, TimeLord::Panel::Value_Channel3_Strip);
   makeMeter(this, Vec(142.83, 84.42), 5, TimeLord::Panel::Value_Channel2_Strip);
   makeMeter(this, Vec(142.00, 39.78), 5, TimeLord::Panel::Value_Channel1_Strip);
}

