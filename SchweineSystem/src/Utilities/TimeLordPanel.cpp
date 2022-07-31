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

   configSwitch(Panel::Channel8_Silence, 0.0f, 1.0f, 0.0f, "Channel8_Silence");
   configSwitch(Panel::Channel7_Silence, 0.0f, 1.0f, 0.0f, "Channel7_Silence");
   configSwitch(Panel::Channel6_Silence, 0.0f, 1.0f, 0.0f, "Channel6_Silence");
   configSwitch(Panel::Channel5_Silence, 0.0f, 1.0f, 0.0f, "Channel5_Silence");
   configSwitch(Panel::Channel4_Silence, 0.0f, 1.0f, 0.0f, "Channel4_Silence");
   configSwitch(Panel::Channel3_Silence, 0.0f, 1.0f, 0.0f, "Channel3_Silence");
   configSwitch(Panel::Channel2_Silence, 0.0f, 1.0f, 0.0f, "Channel2_Silence");
   configSwitch(Panel::Channel1_Silence, 0.0f, 1.0f, 0.0f, "Channel1_Silence");

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

   configPixels(Panel::Pixels_Display, 60, 120, "Display");

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
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/TimeLord.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(122.58, 330.46), TimeLord::Panel::ModeManual);
   makeButton(this, Vec(171.34, 267.56), TimeLord::Panel::Display);
   makeButton(this, Vec(150.54, 108.42), TimeLord::Panel::BankUp);

   makeSwitch(this, Vec(107.59, 289.03), TimeLord::Panel::Channel8_Silence);
   makeSwitch(this, Vec(107.59, 251.03), TimeLord::Panel::Channel7_Silence);
   makeSwitch(this, Vec(107.59, 213.03), TimeLord::Panel::Channel6_Silence);
   makeSwitch(this, Vec(107.59, 175.03), TimeLord::Panel::Channel5_Silence);
   makeSwitch(this, Vec(107.59, 137.03), TimeLord::Panel::Channel4_Silence);
   makeSwitch(this, Vec(107.59, 99.03), TimeLord::Panel::Channel3_Silence);
   makeSwitch(this, Vec(107.59, 61.03), TimeLord::Panel::Channel2_Silence);
   makeSwitch(this, Vec(107.59, 23.03), TimeLord::Panel::Channel1_Silence);

   makeInput(this, Vec(203.59, 355.83),  TimeLord::Panel::Upload);
   makeInput(this, Vec(121.35, 355.83),  TimeLord::Panel::ModeCV);
   makeInput(this, Vec(65.58, 355.83),  TimeLord::Panel::Reset);
   makeInput(this, Vec(31.38, 355.48),  TimeLord::Panel::Clock);
   makeInput(this, Vec(32.07, 289.03),  TimeLord::Panel::Channel8_Pass);
   makeInput(this, Vec(32.07, 251.03),  TimeLord::Panel::Channel7_Pass);
   makeInput(this, Vec(32.07, 213.03),  TimeLord::Panel::Channel6_Pass);
   makeInput(this, Vec(32.07, 175.03),  TimeLord::Panel::Channel5_Pass);
   makeInput(this, Vec(32.07, 137.03),  TimeLord::Panel::Channel4_Pass);
   makeInput(this, Vec(32.07, 99.03),  TimeLord::Panel::Channel3_Pass);
   makeInput(this, Vec(32.07, 61.03),  TimeLord::Panel::Channel2_Pass);
   makeInput(this, Vec(32.07, 23.03),  TimeLord::Panel::Channel1_Pass);

   makeOutput(this, Vec(204.37, 289.03), TimeLord::Panel::Channel8_Output);
   makeOutput(this, Vec(204.37, 251.03), TimeLord::Panel::Channel7_Output);
   makeOutput(this, Vec(204.37, 213.03), TimeLord::Panel::Channel6_Output);
   makeOutput(this, Vec(204.37, 175.03), TimeLord::Panel::Channel5_Output);
   makeOutput(this, Vec(204.37, 137.03), TimeLord::Panel::Channel4_Output);
   makeOutput(this, Vec(204.37, 99.03), TimeLord::Panel::Channel3_Output);
   makeOutput(this, Vec(204.37, 61.03), TimeLord::Panel::Channel2_Output);
   makeOutput(this, Vec(204.37, 23.03), TimeLord::Panel::Channel1_Output);

   makeLED(this, Vec(145.23, 359.60), TimeLord::Panel::RGB_Internal_Status);
   makeLED(this, Vec(145.23, 345.04), TimeLord::Panel::RGB_Remote_Status);
   makeLED(this, Vec(145.23, 330.48), TimeLord::Panel::RGB_Input_Status);

   makeLCD(this, Vec(162.00, 96.42), 1, TimeLord::Panel::Text_Bank, TimeLord::Panel::RGB_Bank);
   makeLCD(this, Vec(48.48, 277.03), 3, TimeLord::Panel::Text_Channel8_Value, TimeLord::Panel::RGB_Channel8_Value);
   makeLCD(this, Vec(48.48, 239.03), 3, TimeLord::Panel::Text_Channel7_Value, TimeLord::Panel::RGB_Channel7_Value);
   makeLCD(this, Vec(48.48, 201.03), 3, TimeLord::Panel::Text_Channel6_Value, TimeLord::Panel::RGB_Channel6_Value);
   makeLCD(this, Vec(48.48, 163.03), 3, TimeLord::Panel::Text_Channel5_Value, TimeLord::Panel::RGB_Channel5_Value);
   makeLCD(this, Vec(48.48, 125.03), 3, TimeLord::Panel::Text_Channel4_Value, TimeLord::Panel::RGB_Channel4_Value);
   makeLCD(this, Vec(48.48, 87.03), 3, TimeLord::Panel::Text_Channel3_Value, TimeLord::Panel::RGB_Channel3_Value);
   makeLCD(this, Vec(48.48, 49.03), 3, TimeLord::Panel::Text_Channel2_Value, TimeLord::Panel::RGB_Channel2_Value);
   makeLCD(this, Vec(48.48, 11.03), 3, TimeLord::Panel::Text_Channel1_Value, TimeLord::Panel::RGB_Channel1_Value);

   makeOLED(this, Vec(120.00, 133.59), TimeLord::Panel::Pixels_Display, 60, 120);

   makeMeter(this, Vec(220.31, 276.03), 5, TimeLord::Panel::Value_Channel8_Strip);
   makeMeter(this, Vec(220.31, 238.03), 5, TimeLord::Panel::Value_Channel7_Strip);
   makeMeter(this, Vec(220.31, 200.03), 5, TimeLord::Panel::Value_Channel6_Strip);
   makeMeter(this, Vec(220.31, 162.03), 5, TimeLord::Panel::Value_Channel5_Strip);
   makeMeter(this, Vec(220.31, 124.03), 5, TimeLord::Panel::Value_Channel4_Strip);
   makeMeter(this, Vec(220.31, 86.03), 5, TimeLord::Panel::Value_Channel3_Strip);
   makeMeter(this, Vec(220.31, 48.03), 5, TimeLord::Panel::Value_Channel2_Strip);
   makeMeter(this, Vec(220.31, 10.03), 5, TimeLord::Panel::Value_Channel1_Strip);
}

