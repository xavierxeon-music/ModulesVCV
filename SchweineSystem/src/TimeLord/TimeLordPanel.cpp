#include "TimeLordPanel.h"
#include "TimeLord.h"

#include <SvinMaster.h>
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
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/TimeLord/TimeLord.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(124.58, 326.46), TimeLord::Panel::ModeManual);
   makeButton(this, Vec(162.42, 274.56), TimeLord::Panel::Display);
   makeButton(this, Vec(148.00, 87.52), TimeLord::Panel::BankUp);

   makeInput(this, Vec(209.59, 355.83), TimeLord::Panel::Upload);
   makeInput(this, Vec(123.35, 355.83), TimeLord::Panel::ModeCV);
   makeInput(this, Vec(65.58, 355.83), TimeLord::Panel::Reset);
   makeInput(this, Vec(31.38, 355.48), TimeLord::Panel::Clock);
   makeInput(this, Vec(34.07, 289.03), TimeLord::Panel::Channel8_Pass);
   makeInput(this, Vec(34.07, 251.03), TimeLord::Panel::Channel7_Pass);
   makeInput(this, Vec(34.07, 213.03), TimeLord::Panel::Channel6_Pass);
   makeInput(this, Vec(34.07, 175.03), TimeLord::Panel::Channel5_Pass);
   makeInput(this, Vec(34.07, 137.03), TimeLord::Panel::Channel4_Pass);
   makeInput(this, Vec(34.07, 99.03), TimeLord::Panel::Channel3_Pass);
   makeInput(this, Vec(34.07, 61.03), TimeLord::Panel::Channel2_Pass);
   makeInput(this, Vec(34.07, 23.03), TimeLord::Panel::Channel1_Pass);

   makeOutput(this, Vec(204.37, 289.03), TimeLord::Panel::Channel8_Output);
   makeOutput(this, Vec(204.37, 251.03), TimeLord::Panel::Channel7_Output);
   makeOutput(this, Vec(204.37, 213.03), TimeLord::Panel::Channel6_Output);
   makeOutput(this, Vec(204.37, 175.03), TimeLord::Panel::Channel5_Output);
   makeOutput(this, Vec(204.37, 137.03), TimeLord::Panel::Channel4_Output);
   makeOutput(this, Vec(204.37, 99.03), TimeLord::Panel::Channel3_Output);
   makeOutput(this, Vec(204.37, 61.03), TimeLord::Panel::Channel2_Output);
   makeOutput(this, Vec(204.37, 23.03), TimeLord::Panel::Channel1_Output);

   makeLED(this, Vec(147.23, 359.60), TimeLord::Panel::RGB_Internal_Status);
   makeLED(this, Vec(147.23, 345.04), TimeLord::Panel::RGB_Remote_Status);
   makeLED(this, Vec(147.23, 330.48), TimeLord::Panel::RGB_Input_Status);

   makeLCD(this, Vec(138.00, 98.63), 1, TimeLord::Panel::Text_Bank);
   makeLCD(this, Vec(50.48, 277.03), 3, TimeLord::Panel::Text_Channel8_Value);
   makeLCD(this, Vec(50.48, 239.03), 3, TimeLord::Panel::Text_Channel7_Value);
   makeLCD(this, Vec(50.48, 201.03), 3, TimeLord::Panel::Text_Channel6_Value);
   makeLCD(this, Vec(50.48, 163.03), 3, TimeLord::Panel::Text_Channel5_Value);
   makeLCD(this, Vec(50.48, 125.03), 3, TimeLord::Panel::Text_Channel4_Value);
   makeLCD(this, Vec(50.48, 87.03), 3, TimeLord::Panel::Text_Channel3_Value);
   makeLCD(this, Vec(50.48, 49.03), 3, TimeLord::Panel::Text_Channel2_Value);
   makeLCD(this, Vec(50.48, 11.03), 3, TimeLord::Panel::Text_Channel1_Value);

   makeOLED(this, Vec(117.00, 137.59), TimeLord::Panel::Pixels_Display, 60, 120);

   makeMeter(this, Vec(220.31, 276.03), 5, TimeLord::Panel::Value_Channel8_Strip);
   makeMeter(this, Vec(220.31, 238.03), 5, TimeLord::Panel::Value_Channel7_Strip);
   makeMeter(this, Vec(220.31, 200.03), 5, TimeLord::Panel::Value_Channel6_Strip);
   makeMeter(this, Vec(220.31, 162.03), 5, TimeLord::Panel::Value_Channel5_Strip);
   makeMeter(this, Vec(220.31, 124.03), 5, TimeLord::Panel::Value_Channel4_Strip);
   makeMeter(this, Vec(220.31, 86.03), 5, TimeLord::Panel::Value_Channel3_Strip);
   makeMeter(this, Vec(220.31, 48.03), 5, TimeLord::Panel::Value_Channel2_Strip);
   makeMeter(this, Vec(220.31, 10.03), 5, TimeLord::Panel::Value_Channel1_Strip);
}
