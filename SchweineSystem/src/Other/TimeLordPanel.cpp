#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void TimeLord::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Mode, "Mode");
   configButton(Panel::BankUp, "BankUp");

   configInput(Panel::Pass, "Pass");
   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");
   configInput(Panel::Channel8_Pass, "Channel8_Pass");
   configInput(Panel::Channel7_Pass, "Channel7_Pass");
   configInput(Panel::Channel6_Pass, "Channel6_Pass");
   configInput(Panel::Channel5_Pass, "Channel5_Pass");
   configInput(Panel::Channel4_Pass, "Channel4_Pass");
   configInput(Panel::Channel3_Pass, "Channel3_Pass");
   configInput(Panel::Channel2_Pass, "Channel2_Pass");
   configInput(Panel::Channel1_Pass, "Channel1_Pass");

   configOutput(Panel::Channel8_Output, "Channel8_Output");
   configOutput(Panel::Channel7_Output, "Channel7_Output");
   configOutput(Panel::Channel6_Output, "Channel6_Output");
   configOutput(Panel::Channel5_Output, "Channel5_Output");
   configOutput(Panel::Channel4_Output, "Channel4_Output");
   configOutput(Panel::Channel3_Output, "Channel3_Output");
   configOutput(Panel::Channel2_Output, "Channel2_Output");
   configOutput(Panel::Channel1_Output, "Channel1_Output");

   configText(Panel::Text_Channel8_Value, "Channel8_Value");
   configText(Panel::Text_Channel7_Value, "Channel7_Value");
   configText(Panel::Text_Channel6_Value, "Channel6_Value");
   configText(Panel::Text_Channel5_Value, "Channel5_Value");
   configText(Panel::Text_Channel4_Value, "Channel4_Value");
   configText(Panel::Text_Channel3_Value, "Channel3_Value");
   configText(Panel::Text_Channel2_Value, "Channel2_Value");
   configText(Panel::Text_Channel1_Value, "Channel1_Value");

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

   makeButton(this, Vec(101.36, 337.52), TimeLord::Panel::Mode);
   makeButton(this, Vec(101.36, 357.98), TimeLord::Panel::BankUp);

   makeInput(this, Vec(125.83, 355.83),  TimeLord::Panel::Pass);
   makeInput(this, Vec(57.65, 355.83),  TimeLord::Panel::Reset);
   makeInput(this, Vec(24.17, 355.83),  TimeLord::Panel::Clock);
   makeInput(this, Vec(31.55, 242.07),  TimeLord::Panel::Channel8_Pass);
   makeInput(this, Vec(31.55, 210.94),  TimeLord::Panel::Channel7_Pass);
   makeInput(this, Vec(31.55, 179.81),  TimeLord::Panel::Channel6_Pass);
   makeInput(this, Vec(31.55, 148.68),  TimeLord::Panel::Channel5_Pass);
   makeInput(this, Vec(31.55, 117.56),  TimeLord::Panel::Channel4_Pass);
   makeInput(this, Vec(31.55, 86.43),  TimeLord::Panel::Channel3_Pass);
   makeInput(this, Vec(31.55, 55.30),  TimeLord::Panel::Channel2_Pass);
   makeInput(this, Vec(31.55, 24.17),  TimeLord::Panel::Channel1_Pass);

   makeOutput(this, Vec(118.86, 242.07), TimeLord::Panel::Channel8_Output);
   makeOutput(this, Vec(118.86, 210.94), TimeLord::Panel::Channel7_Output);
   makeOutput(this, Vec(118.86, 179.81), TimeLord::Panel::Channel6_Output);
   makeOutput(this, Vec(118.86, 148.68), TimeLord::Panel::Channel5_Output);
   makeOutput(this, Vec(118.86, 117.56), TimeLord::Panel::Channel4_Output);
   makeOutput(this, Vec(118.86, 86.43), TimeLord::Panel::Channel3_Output);
   makeOutput(this, Vec(118.86, 55.30), TimeLord::Panel::Channel2_Output);
   makeOutput(this, Vec(118.86, 24.17), TimeLord::Panel::Channel1_Output);

   makeLCD(this, Vec(47.96, 230.07), 3, TimeLord::Panel::Text_Channel8_Value, TimeLord::Panel::RGB_Channel8_Value);
   makeLCD(this, Vec(47.96, 198.94), 3, TimeLord::Panel::Text_Channel7_Value, TimeLord::Panel::RGB_Channel7_Value);
   makeLCD(this, Vec(47.96, 167.81), 3, TimeLord::Panel::Text_Channel6_Value, TimeLord::Panel::RGB_Channel6_Value);
   makeLCD(this, Vec(47.96, 136.68), 3, TimeLord::Panel::Text_Channel5_Value, TimeLord::Panel::RGB_Channel5_Value);
   makeLCD(this, Vec(47.96, 105.56), 3, TimeLord::Panel::Text_Channel4_Value, TimeLord::Panel::RGB_Channel4_Value);
   makeLCD(this, Vec(47.96, 74.43), 3, TimeLord::Panel::Text_Channel3_Value, TimeLord::Panel::RGB_Channel3_Value);
   makeLCD(this, Vec(47.96, 43.30), 3, TimeLord::Panel::Text_Channel2_Value, TimeLord::Panel::RGB_Channel2_Value);
   makeLCD(this, Vec(47.96, 12.17), 3, TimeLord::Panel::Text_Channel1_Value, TimeLord::Panel::RGB_Channel1_Value);

   makeOLED(this, Vec(10.00, 259.59), TimeLord::Panel::Pixels_Display, 128, 64);

   makeMeter(this, Vec(134.80, 229.07), 5, TimeLord::Panel::Value_Channel8_Strip);
   makeMeter(this, Vec(134.80, 197.94), 5, TimeLord::Panel::Value_Channel7_Strip);
   makeMeter(this, Vec(134.80, 166.81), 5, TimeLord::Panel::Value_Channel6_Strip);
   makeMeter(this, Vec(134.80, 135.68), 5, TimeLord::Panel::Value_Channel5_Strip);
   makeMeter(this, Vec(134.80, 104.56), 5, TimeLord::Panel::Value_Channel4_Strip);
   makeMeter(this, Vec(134.80, 73.43), 5, TimeLord::Panel::Value_Channel3_Strip);
   makeMeter(this, Vec(134.80, 42.30), 5, TimeLord::Panel::Value_Channel2_Strip);
   makeMeter(this, Vec(134.80, 11.17), 5, TimeLord::Panel::Value_Channel1_Strip);
}

