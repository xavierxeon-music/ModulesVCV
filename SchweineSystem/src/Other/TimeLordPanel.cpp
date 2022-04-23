#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

TimeLord::Panel::Panel()
{
};


void TimeLord::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configParam(Panel::Value_Bank_Display, 0.f, 10, 0.f, "");
   configParam(Panel::Value_Channel8_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel7_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel6_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel5_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel4_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel3_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel2_Display, 0.f, 1000, 0.f, "");
   configParam(Panel::Value_Channel1_Display, 0.f, 1000, 0.f, "");

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
}

SvgPanel* TimeLordWidget::setup(TimeLord* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/TimeLord.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(38.70, 247.47), TimeLord::Panel::Mode, TimeLord::Panel::Red_Mode);
   makeButton(this, Vec(38.23, 117.31), TimeLord::Panel::Bank_Up, TimeLord::Panel::Red_Bank_Up);

   makeInput(this, Vec(38.69, 344.74),  TimeLord::Panel::Reset);
   makeInput(this, Vec(38.69, 298.64),  TimeLord::Panel::Clock);

   makeOutput(this, Vec(155.00, 344.45), TimeLord::Panel::Channel8_Output);
   makeOutput(this, Vec(155.00, 298.69), TimeLord::Panel::Channel7_Output);
   makeOutput(this, Vec(155.00, 252.94), TimeLord::Panel::Channel6_Output);
   makeOutput(this, Vec(155.00, 207.19), TimeLord::Panel::Channel5_Output);
   makeOutput(this, Vec(155.00, 161.43), TimeLord::Panel::Channel4_Output);
   makeOutput(this, Vec(155.00, 115.68), TimeLord::Panel::Channel3_Output);
   makeOutput(this, Vec(155.00, 69.93), TimeLord::Panel::Channel2_Output);
   makeOutput(this, Vec(155.00, 24.17), TimeLord::Panel::Channel1_Output);

   makeLight(this, Vec(39.15, 225.19), TimeLord::Panel::Red_Current);
   makeLight(this, Vec(39.15, 201.58), TimeLord::Panel::Red_Count);
   makeLight(this, Vec(38.99, 177.46), TimeLord::Panel::Red_Length);
   makeLight(this, Vec(38.99, 153.34), TimeLord::Panel::Red_Division);
   makeLight(this, Vec(166.18, 366.18), TimeLord::Panel::Red_Channel8_Status5);
   makeLight(this, Vec(156.77, 366.18), TimeLord::Panel::Red_Channel8_Status4);
   makeLight(this, Vec(147.35, 366.18), TimeLord::Panel::Red_Channel8_Status3);
   makeLight(this, Vec(137.94, 366.18), TimeLord::Panel::Red_Channel8_Status2);
   makeLight(this, Vec(128.53, 366.18), TimeLord::Panel::Red_Channel8_Status1);
   makeLight(this, Vec(166.18, 320.43), TimeLord::Panel::Red_Channel7_Status5);
   makeLight(this, Vec(156.77, 320.43), TimeLord::Panel::Red_Channel7_Status4);
   makeLight(this, Vec(147.35, 320.43), TimeLord::Panel::Red_Channel7_Status3);
   makeLight(this, Vec(137.94, 320.43), TimeLord::Panel::Red_Channel7_Status2);
   makeLight(this, Vec(128.53, 320.43), TimeLord::Panel::Red_Channel7_Status1);
   makeLight(this, Vec(166.18, 274.67), TimeLord::Panel::Red_Channel6_Status5);
   makeLight(this, Vec(156.77, 274.67), TimeLord::Panel::Red_Channel6_Status4);
   makeLight(this, Vec(147.35, 274.67), TimeLord::Panel::Red_Channel6_Status3);
   makeLight(this, Vec(137.94, 274.67), TimeLord::Panel::Red_Channel6_Status2);
   makeLight(this, Vec(128.53, 274.67), TimeLord::Panel::Red_Channel6_Status1);
   makeLight(this, Vec(166.18, 228.92), TimeLord::Panel::Red_Channel5_Status5);
   makeLight(this, Vec(156.77, 228.92), TimeLord::Panel::Red_Channel5_Status4);
   makeLight(this, Vec(147.35, 228.92), TimeLord::Panel::Red_Channel5_Status3);
   makeLight(this, Vec(137.94, 228.92), TimeLord::Panel::Red_Channel5_Status2);
   makeLight(this, Vec(128.53, 228.92), TimeLord::Panel::Red_Channel5_Status1);
   makeLight(this, Vec(166.18, 183.17), TimeLord::Panel::Red_Channel4_Status5);
   makeLight(this, Vec(156.77, 183.17), TimeLord::Panel::Red_Channel4_Status4);
   makeLight(this, Vec(147.35, 183.17), TimeLord::Panel::Red_Channel4_Status3);
   makeLight(this, Vec(137.94, 183.17), TimeLord::Panel::Red_Channel4_Status2);
   makeLight(this, Vec(128.53, 183.17), TimeLord::Panel::Red_Channel4_Status1);
   makeLight(this, Vec(166.18, 137.41), TimeLord::Panel::Red_Channel3_Status5);
   makeLight(this, Vec(156.77, 137.41), TimeLord::Panel::Red_Channel3_Status4);
   makeLight(this, Vec(147.35, 137.41), TimeLord::Panel::Red_Channel3_Status3);
   makeLight(this, Vec(137.94, 137.41), TimeLord::Panel::Red_Channel3_Status2);
   makeLight(this, Vec(128.53, 137.41), TimeLord::Panel::Red_Channel3_Status1);
   makeLight(this, Vec(166.18, 91.66), TimeLord::Panel::Red_Channel2_Status5);
   makeLight(this, Vec(156.77, 91.66), TimeLord::Panel::Red_Channel2_Status4);
   makeLight(this, Vec(147.35, 91.66), TimeLord::Panel::Red_Channel2_Status3);
   makeLight(this, Vec(137.94, 91.66), TimeLord::Panel::Red_Channel2_Status2);
   makeLight(this, Vec(128.53, 91.66), TimeLord::Panel::Red_Channel2_Status1);
   makeLight(this, Vec(166.18, 45.90), TimeLord::Panel::Red_Channel1_Status5);
   makeLight(this, Vec(156.77, 45.90), TimeLord::Panel::Red_Channel1_Status4);
   makeLight(this, Vec(147.35, 45.90), TimeLord::Panel::Red_Channel1_Status3);
   makeLight(this, Vec(137.94, 45.90), TimeLord::Panel::Red_Channel1_Status2);
   makeLight(this, Vec(128.53, 45.90), TimeLord::Panel::Red_Channel1_Status1);

   makeDisplay(this, Vec(29.23, 79.79), 1, TimeLord::Panel::Value_Bank_Display, TimeLord::Panel::Red_Bank_Display);
   makeDisplay(this, Vec(87.00, 332.87), 3, TimeLord::Panel::Value_Channel8_Display, TimeLord::Panel::Red_Channel8_Display);
   makeDisplay(this, Vec(87.00, 287.12), 3, TimeLord::Panel::Value_Channel7_Display, TimeLord::Panel::Red_Channel7_Display);
   makeDisplay(this, Vec(87.00, 241.37), 3, TimeLord::Panel::Value_Channel6_Display, TimeLord::Panel::Red_Channel6_Display);
   makeDisplay(this, Vec(87.00, 195.61), 3, TimeLord::Panel::Value_Channel5_Display, TimeLord::Panel::Red_Channel5_Display);
   makeDisplay(this, Vec(87.00, 149.86), 3, TimeLord::Panel::Value_Channel4_Display, TimeLord::Panel::Red_Channel4_Display);
   makeDisplay(this, Vec(87.00, 104.10), 3, TimeLord::Panel::Value_Channel3_Display, TimeLord::Panel::Red_Channel3_Display);
   makeDisplay(this, Vec(87.00, 58.35), 3, TimeLord::Panel::Value_Channel2_Display, TimeLord::Panel::Red_Channel2_Display);
   makeDisplay(this, Vec(87.00, 12.60), 3, TimeLord::Panel::Value_Channel1_Display, TimeLord::Panel::Red_Channel1_Display);

   return mainPanel;
}

