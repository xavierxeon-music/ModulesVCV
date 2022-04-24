#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void VCMCReceiver::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::ClockOverride, "ClockOverride");

   configOutput(Panel::Reset, "Reset");
   configOutput(Panel::Clock, "Clock");
   configOutput(Panel::Channel8_Gate_BitOut1, "Channel8_Gate_BitOut1");
   configOutput(Panel::Channel8_Slider_Output, "Channel8_Slider_Output");
   configOutput(Panel::Channel8_CV_Output, "Channel8_CV_Output");
   configOutput(Panel::Channel7_Gate1_BitOut1, "Channel7_Gate1_BitOut1");
   configOutput(Panel::Channel7_Slider1_Output, "Channel7_Slider1_Output");
   configOutput(Panel::Channel7_CV1_Output, "Channel7_CV1_Output");
   configOutput(Panel::Channel6_Gate2_BitOut1, "Channel6_Gate2_BitOut1");
   configOutput(Panel::Channel6_Slider2_Output, "Channel6_Slider2_Output");
   configOutput(Panel::Channel6_CV2_Output, "Channel6_CV2_Output");
   configOutput(Panel::Channel5_Gate3_BitOut1, "Channel5_Gate3_BitOut1");
   configOutput(Panel::Channel5_Slider3_Output, "Channel5_Slider3_Output");
   configOutput(Panel::Channel5_CV3_Output, "Channel5_CV3_Output");
   configOutput(Panel::Channel4_Gate4_BitOut1, "Channel4_Gate4_BitOut1");
   configOutput(Panel::Channel4_Slider4_Output, "Channel4_Slider4_Output");
   configOutput(Panel::Channel4_CV4_Output, "Channel4_CV4_Output");
   configOutput(Panel::Channel3_Gate5_BitOut1, "Channel3_Gate5_BitOut1");
   configOutput(Panel::Channel3_Slider5_Output, "Channel3_Slider5_Output");
   configOutput(Panel::Channel3_CV5_Output, "Channel3_CV5_Output");
   configOutput(Panel::Channel2_Gate6_BitOut1, "Channel2_Gate6_BitOut1");
   configOutput(Panel::Channel2_Slider6_Output, "Channel2_Slider6_Output");
   configOutput(Panel::Channel2_CV6_Output, "Channel2_CV6_Output");
   configOutput(Panel::Channel1_Gate7_BitOut1, "Channel1_Gate7_BitOut1");
   configOutput(Panel::Channel1_Slider7_Output, "Channel1_Slider7_Output");
   configOutput(Panel::Channel1_CV7_Output, "Channel1_CV7_Output");

   configDisplay(Panel::Text_Clock, "Clock");

   configMeter(Panel::Value_Channel8_Slider_Strip, "Channel8_Slider_Strip");
   configMeter(Panel::Value_Channel8_CV_Strip, "Channel8_CV_Strip");
   configMeter(Panel::Value_Channel7_Slider1_Strip, "Channel7_Slider1_Strip");
   configMeter(Panel::Value_Channel7_CV1_Strip, "Channel7_CV1_Strip");
   configMeter(Panel::Value_Channel6_Slider2_Strip, "Channel6_Slider2_Strip");
   configMeter(Panel::Value_Channel6_CV2_Strip, "Channel6_CV2_Strip");
   configMeter(Panel::Value_Channel5_Slider3_Strip, "Channel5_Slider3_Strip");
   configMeter(Panel::Value_Channel5_CV3_Strip, "Channel5_CV3_Strip");
   configMeter(Panel::Value_Channel4_Slider4_Strip, "Channel4_Slider4_Strip");
   configMeter(Panel::Value_Channel4_CV4_Strip, "Channel4_CV4_Strip");
   configMeter(Panel::Value_Channel3_Slider5_Strip, "Channel3_Slider5_Strip");
   configMeter(Panel::Value_Channel3_CV5_Strip, "Channel3_CV5_Strip");
   configMeter(Panel::Value_Channel2_Slider6_Strip, "Channel2_Slider6_Strip");
   configMeter(Panel::Value_Channel2_CV6_Strip, "Channel2_CV6_Strip");
   configMeter(Panel::Value_Channel1_Slider7_Strip, "Channel1_Slider7_Strip");
   configMeter(Panel::Value_Channel1_CV7_Strip, "Channel1_CV7_Strip");
}

void VCMCReceiverWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/VCMCReceiver.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(113.88, 322.08), VCMCReceiver::Panel::Connect, VCMCReceiver::Panel::RGB_Connect);

   makeInput(this, Vec(36.13, 321.96),  VCMCReceiver::Panel::ClockOverride);

   makeOutput(this, Vec(71.30, 321.96), VCMCReceiver::Panel::Reset);
   makeOutput(this, Vec(36.13, 355.59), VCMCReceiver::Panel::Clock);
   makeOutput(this, Vec(32.19, 274.65), VCMCReceiver::Panel::Channel8_Gate_BitOut1);
   makeOutput(this, Vec(114.88, 274.65), VCMCReceiver::Panel::Channel8_Slider_Output);
   makeOutput(this, Vec(73.72, 274.65), VCMCReceiver::Panel::Channel8_CV_Output);
   makeOutput(this, Vec(32.83, 242.85), VCMCReceiver::Panel::Channel7_Gate1_BitOut1);
   makeOutput(this, Vec(115.52, 242.85), VCMCReceiver::Panel::Channel7_Slider1_Output);
   makeOutput(this, Vec(74.36, 242.85), VCMCReceiver::Panel::Channel7_CV1_Output);
   makeOutput(this, Vec(32.83, 211.04), VCMCReceiver::Panel::Channel6_Gate2_BitOut1);
   makeOutput(this, Vec(115.52, 211.04), VCMCReceiver::Panel::Channel6_Slider2_Output);
   makeOutput(this, Vec(74.36, 211.04), VCMCReceiver::Panel::Channel6_CV2_Output);
   makeOutput(this, Vec(32.83, 179.24), VCMCReceiver::Panel::Channel5_Gate3_BitOut1);
   makeOutput(this, Vec(115.52, 179.24), VCMCReceiver::Panel::Channel5_Slider3_Output);
   makeOutput(this, Vec(74.36, 179.24), VCMCReceiver::Panel::Channel5_CV3_Output);
   makeOutput(this, Vec(32.83, 147.44), VCMCReceiver::Panel::Channel4_Gate4_BitOut1);
   makeOutput(this, Vec(115.52, 147.44), VCMCReceiver::Panel::Channel4_Slider4_Output);
   makeOutput(this, Vec(74.36, 147.44), VCMCReceiver::Panel::Channel4_CV4_Output);
   makeOutput(this, Vec(32.83, 115.64), VCMCReceiver::Panel::Channel3_Gate5_BitOut1);
   makeOutput(this, Vec(115.52, 115.64), VCMCReceiver::Panel::Channel3_Slider5_Output);
   makeOutput(this, Vec(74.36, 115.64), VCMCReceiver::Panel::Channel3_CV5_Output);
   makeOutput(this, Vec(32.83, 83.84), VCMCReceiver::Panel::Channel2_Gate6_BitOut1);
   makeOutput(this, Vec(115.52, 83.84), VCMCReceiver::Panel::Channel2_Slider6_Output);
   makeOutput(this, Vec(74.36, 83.84), VCMCReceiver::Panel::Channel2_CV6_Output);
   makeOutput(this, Vec(32.83, 52.03), VCMCReceiver::Panel::Channel1_Gate7_BitOut1);
   makeOutput(this, Vec(115.52, 52.03), VCMCReceiver::Panel::Channel1_Slider7_Output);
   makeOutput(this, Vec(74.36, 52.03), VCMCReceiver::Panel::Channel1_CV7_Output);

   makeLight(this, Vec(53.38, 274.65), VCMCReceiver::Panel::RGB_Channel8_Gate_Status1);
   makeLight(this, Vec(54.02, 242.85), VCMCReceiver::Panel::RGB_Channel7_Gate1_Status1);
   makeLight(this, Vec(54.02, 211.04), VCMCReceiver::Panel::RGB_Channel6_Gate2_Status1);
   makeLight(this, Vec(54.02, 179.24), VCMCReceiver::Panel::RGB_Channel5_Gate3_Status1);
   makeLight(this, Vec(54.02, 147.44), VCMCReceiver::Panel::RGB_Channel4_Gate4_Status1);
   makeLight(this, Vec(54.02, 115.64), VCMCReceiver::Panel::RGB_Channel3_Gate5_Status1);
   makeLight(this, Vec(54.02, 83.83), VCMCReceiver::Panel::RGB_Channel2_Gate6_Status1);
   makeLight(this, Vec(54.02, 52.03), VCMCReceiver::Panel::RGB_Channel1_Gate7_Status1);

   makeDisplay(this, Vec(58.10, 343.59), 3, VCMCReceiver::Panel::Text_Clock, VCMCReceiver::Panel::RGB_Clock);

   makeMeter(this, Vec(131.70, 261.65), 5, VCMCReceiver::Panel::Value_Channel8_Slider_Strip);
   makeMeter(this, Vec(90.54, 261.65), 5, VCMCReceiver::Panel::Value_Channel8_CV_Strip);
   makeMeter(this, Vec(132.34, 229.85), 5, VCMCReceiver::Panel::Value_Channel7_Slider1_Strip);
   makeMeter(this, Vec(91.18, 229.85), 5, VCMCReceiver::Panel::Value_Channel7_CV1_Strip);
   makeMeter(this, Vec(132.34, 198.04), 5, VCMCReceiver::Panel::Value_Channel6_Slider2_Strip);
   makeMeter(this, Vec(91.18, 198.04), 5, VCMCReceiver::Panel::Value_Channel6_CV2_Strip);
   makeMeter(this, Vec(132.34, 166.24), 5, VCMCReceiver::Panel::Value_Channel5_Slider3_Strip);
   makeMeter(this, Vec(91.18, 166.24), 5, VCMCReceiver::Panel::Value_Channel5_CV3_Strip);
   makeMeter(this, Vec(132.34, 134.44), 5, VCMCReceiver::Panel::Value_Channel4_Slider4_Strip);
   makeMeter(this, Vec(91.18, 134.44), 5, VCMCReceiver::Panel::Value_Channel4_CV4_Strip);
   makeMeter(this, Vec(132.34, 102.64), 5, VCMCReceiver::Panel::Value_Channel3_Slider5_Strip);
   makeMeter(this, Vec(91.18, 102.64), 5, VCMCReceiver::Panel::Value_Channel3_CV5_Strip);
   makeMeter(this, Vec(132.34, 70.84), 5, VCMCReceiver::Panel::Value_Channel2_Slider6_Strip);
   makeMeter(this, Vec(91.18, 70.84), 5, VCMCReceiver::Panel::Value_Channel2_CV6_Strip);
   makeMeter(this, Vec(132.34, 39.03), 5, VCMCReceiver::Panel::Value_Channel1_Slider7_Strip);
   makeMeter(this, Vec(91.18, 39.03), 5, VCMCReceiver::Panel::Value_Channel1_CV7_Strip);
}

