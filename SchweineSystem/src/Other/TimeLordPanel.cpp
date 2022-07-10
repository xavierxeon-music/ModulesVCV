#include "TimeLord.h"
#include "TimeLordPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void TimeLord::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::ModeManual, "ModeManual");
   configButton(Panel::Display, "Display");
   configButton(Panel::BankUp, "BankUp");

   configInput(Panel::Upload, "Upload");
   configInput(Panel::ModeCV, "ModeCV");
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

   configText(Panel::Text_Bank, "Bank");
   configText(Panel::Text_Channel8_Value, "Channel8_Value");
   configText(Panel::Text_Channel7_Value, "Channel7_Value");
   configText(Panel::Text_Channel6_Value, "Channel6_Value");
   configText(Panel::Text_Channel5_Value, "Channel5_Value");
   configText(Panel::Text_Channel4_Value, "Channel4_Value");
   configText(Panel::Text_Channel3_Value, "Channel3_Value");
   configText(Panel::Text_Channel2_Value, "Channel2_Value");
   configText(Panel::Text_Channel1_Value, "Channel1_Value");

   configPixels(Panel::Pixels_Display, 80, 120, "Display");

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

   makeButton(this, Vec(122.58, 320.46), TimeLord::Panel::ModeManual);
   makeButton(this, Vec(156.51, 255.51), TimeLord::Panel::Display);
   makeButton(this, Vec(143.36, 79.54), TimeLord::Panel::BankUp);

   makeInput(this, Vec(203.59, 345.83),  TimeLord::Panel::Upload);
   makeInput(this, Vec(121.35, 345.83),  TimeLord::Panel::ModeCV);
   makeInput(this, Vec(65.58, 345.83),  TimeLord::Panel::Reset);
   makeInput(this, Vec(31.38, 345.48),  TimeLord::Panel::Clock);
   makeInput(this, Vec(31.67, 295.51),  TimeLord::Panel::Channel8_Pass);
   makeInput(this, Vec(32.07, 259.59),  TimeLord::Panel::Channel7_Pass);
   makeInput(this, Vec(32.07, 223.66),  TimeLord::Panel::Channel6_Pass);
   makeInput(this, Vec(32.07, 187.74),  TimeLord::Panel::Channel5_Pass);
   makeInput(this, Vec(32.07, 151.81),  TimeLord::Panel::Channel4_Pass);
   makeInput(this, Vec(32.07, 115.88),  TimeLord::Panel::Channel3_Pass);
   makeInput(this, Vec(32.07, 79.96),  TimeLord::Panel::Channel2_Pass);
   makeInput(this, Vec(32.07, 44.03),  TimeLord::Panel::Channel1_Pass);

   makeOutput(this, Vec(203.97, 295.51), TimeLord::Panel::Channel8_Output);
   makeOutput(this, Vec(204.37, 259.59), TimeLord::Panel::Channel7_Output);
   makeOutput(this, Vec(204.37, 223.66), TimeLord::Panel::Channel6_Output);
   makeOutput(this, Vec(204.37, 187.74), TimeLord::Panel::Channel5_Output);
   makeOutput(this, Vec(204.37, 151.81), TimeLord::Panel::Channel4_Output);
   makeOutput(this, Vec(204.37, 115.88), TimeLord::Panel::Channel3_Output);
   makeOutput(this, Vec(204.37, 79.96), TimeLord::Panel::Channel2_Output);
   makeOutput(this, Vec(204.37, 44.03), TimeLord::Panel::Channel1_Output);

   makeLED(this, Vec(145.23, 349.60), TimeLord::Panel::RGB_Internal_Status);
   makeLED(this, Vec(145.23, 335.04), TimeLord::Panel::RGB_Remote_Status);
   makeLED(this, Vec(145.23, 320.48), TimeLord::Panel::RGB_Input_Status);

   makeLCD(this, Vec(154.81, 67.54), 1, TimeLord::Panel::Text_Bank, TimeLord::Panel::RGB_Bank);
   makeLCD(this, Vec(48.08, 283.51), 3, TimeLord::Panel::Text_Channel8_Value, TimeLord::Panel::RGB_Channel8_Value);
   makeLCD(this, Vec(48.48, 247.59), 3, TimeLord::Panel::Text_Channel7_Value, TimeLord::Panel::RGB_Channel7_Value);
   makeLCD(this, Vec(48.48, 211.66), 3, TimeLord::Panel::Text_Channel6_Value, TimeLord::Panel::RGB_Channel6_Value);
   makeLCD(this, Vec(48.48, 175.74), 3, TimeLord::Panel::Text_Channel5_Value, TimeLord::Panel::RGB_Channel5_Value);
   makeLCD(this, Vec(48.48, 139.81), 3, TimeLord::Panel::Text_Channel4_Value, TimeLord::Panel::RGB_Channel4_Value);
   makeLCD(this, Vec(48.48, 103.88), 3, TimeLord::Panel::Text_Channel3_Value, TimeLord::Panel::RGB_Channel3_Value);
   makeLCD(this, Vec(48.48, 67.96), 3, TimeLord::Panel::Text_Channel2_Value, TimeLord::Panel::RGB_Channel2_Value);
   makeLCD(this, Vec(48.48, 32.03), 3, TimeLord::Panel::Text_Channel1_Value, TimeLord::Panel::RGB_Channel1_Value);

   makeOLED(this, Vec(105.17, 119.54), TimeLord::Panel::Pixels_Display, 80, 120);

   makeMeter(this, Vec(219.91, 282.51), 5, TimeLord::Panel::Value_Channel8_Strip);
   makeMeter(this, Vec(220.31, 246.59), 5, TimeLord::Panel::Value_Channel7_Strip);
   makeMeter(this, Vec(220.31, 210.66), 5, TimeLord::Panel::Value_Channel6_Strip);
   makeMeter(this, Vec(220.31, 174.74), 5, TimeLord::Panel::Value_Channel5_Strip);
   makeMeter(this, Vec(220.31, 138.81), 5, TimeLord::Panel::Value_Channel4_Strip);
   makeMeter(this, Vec(220.31, 102.88), 5, TimeLord::Panel::Value_Channel3_Strip);
   makeMeter(this, Vec(220.31, 66.96), 5, TimeLord::Panel::Value_Channel2_Strip);
   makeMeter(this, Vec(220.31, 31.03), 5, TimeLord::Panel::Value_Channel1_Strip);
}

