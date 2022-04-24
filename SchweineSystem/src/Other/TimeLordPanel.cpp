#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

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

   makeButton(this, Vec(105.85, 355.83), TimeLord::Panel::Bank_Up);
   makeButton(this, Vec(24.16, 310.77), TimeLord::Panel::Mode);

   makeInput(this, Vec(55.97, 355.83),  TimeLord::Panel::Reset);
   makeInput(this, Vec(25.02, 355.83),  TimeLord::Panel::Clock);

   makeOutput(this, Vec(87.77, 274.84), TimeLord::Panel::Channel8_Output);
   makeOutput(this, Vec(87.77, 241.11), TimeLord::Panel::Channel7_Output);
   makeOutput(this, Vec(87.77, 207.39), TimeLord::Panel::Channel6_Output);
   makeOutput(this, Vec(87.77, 173.67), TimeLord::Panel::Channel5_Output);
   makeOutput(this, Vec(87.77, 139.94), TimeLord::Panel::Channel4_Output);
   makeOutput(this, Vec(87.77, 106.22), TimeLord::Panel::Channel3_Output);
   makeOutput(this, Vec(87.77, 72.49), TimeLord::Panel::Channel2_Output);
   makeOutput(this, Vec(87.77, 38.77), TimeLord::Panel::Channel1_Output);

   makeLight(this, Vec(94.67, 310.59), TimeLord::Panel::RGB_Current);
   makeLight(this, Vec(78.71, 310.60), TimeLord::Panel::RGB_Count);
   makeLight(this, Vec(62.74, 310.77), TimeLord::Panel::RGB_Length);
   makeLight(this, Vec(46.78, 310.77), TimeLord::Panel::RGB_Division);

   makeDisplay(this, Vec(76.31, 343.83), 1, TimeLord::Panel::Text_Bank_Display, TimeLord::Panel::RGB_Bank_Display);
   makeDisplay(this, Vec(20.91, 262.84), 3, TimeLord::Panel::Text_Channel8_Display, TimeLord::Panel::RGB_Channel8_Display);
   makeDisplay(this, Vec(20.91, 229.11), 3, TimeLord::Panel::Text_Channel7_Display, TimeLord::Panel::RGB_Channel7_Display);
   makeDisplay(this, Vec(20.91, 195.39), 3, TimeLord::Panel::Text_Channel6_Display, TimeLord::Panel::RGB_Channel6_Display);
   makeDisplay(this, Vec(20.91, 161.67), 3, TimeLord::Panel::Text_Channel5_Display, TimeLord::Panel::RGB_Channel5_Display);
   makeDisplay(this, Vec(20.91, 127.94), 3, TimeLord::Panel::Text_Channel4_Display, TimeLord::Panel::RGB_Channel4_Display);
   makeDisplay(this, Vec(20.91, 94.22), 3, TimeLord::Panel::Text_Channel3_Display, TimeLord::Panel::RGB_Channel3_Display);
   makeDisplay(this, Vec(20.91, 60.49), 3, TimeLord::Panel::Text_Channel2_Display, TimeLord::Panel::RGB_Channel2_Display);
   makeDisplay(this, Vec(20.91, 26.77), 3, TimeLord::Panel::Text_Channel1_Display, TimeLord::Panel::RGB_Channel1_Display);

   makeMeter(this, Vec(104.00, 261.84), 5, TimeLord::Panel::Value_Channel8_Strip);
   makeMeter(this, Vec(104.00, 228.11), 5, TimeLord::Panel::Value_Channel7_Strip);
   makeMeter(this, Vec(104.00, 194.39), 5, TimeLord::Panel::Value_Channel6_Strip);
   makeMeter(this, Vec(104.00, 160.67), 5, TimeLord::Panel::Value_Channel5_Strip);
   makeMeter(this, Vec(104.00, 126.94), 5, TimeLord::Panel::Value_Channel4_Strip);
   makeMeter(this, Vec(104.00, 93.22), 5, TimeLord::Panel::Value_Channel3_Strip);
   makeMeter(this, Vec(104.00, 59.49), 5, TimeLord::Panel::Value_Channel2_Strip);
   makeMeter(this, Vec(104.00, 25.77), 5, TimeLord::Panel::Value_Channel1_Strip);
}

