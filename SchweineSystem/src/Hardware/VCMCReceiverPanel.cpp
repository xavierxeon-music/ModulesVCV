#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void VCMCReceiver::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

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

   makeButton(this, Vec(115.60, 332.70), VCMCReceiver::Panel::Connect, VCMCReceiver::Panel::RGB_Connect);

   makeInput(this, Vec(52.34, 298.84),  VCMCReceiver::Panel::ClockOverride);

   makeOutput(this, Vec(52.34, 332.47), VCMCReceiver::Panel::Reset);
   makeOutput(this, Vec(86.02, 298.84), VCMCReceiver::Panel::Clock);
   makeOutput(this, Vec(31.17, 259.13), VCMCReceiver::Panel::Channel8_Gate_BitOut1);
   makeOutput(this, Vec(117.69, 259.73), VCMCReceiver::Panel::Channel8_Slider_Output);
   makeOutput(this, Vec(78.70, 259.73), VCMCReceiver::Panel::Channel8_CV_Output);
   makeOutput(this, Vec(31.17, 227.19), VCMCReceiver::Panel::Channel7_Gate1_BitOut1);
   makeOutput(this, Vec(117.69, 227.78), VCMCReceiver::Panel::Channel7_Slider1_Output);
   makeOutput(this, Vec(78.70, 227.78), VCMCReceiver::Panel::Channel7_CV1_Output);
   makeOutput(this, Vec(31.17, 195.24), VCMCReceiver::Panel::Channel6_Gate2_BitOut1);
   makeOutput(this, Vec(117.69, 195.83), VCMCReceiver::Panel::Channel6_Slider2_Output);
   makeOutput(this, Vec(78.70, 195.83), VCMCReceiver::Panel::Channel6_CV2_Output);
   makeOutput(this, Vec(31.17, 163.29), VCMCReceiver::Panel::Channel5_Gate3_BitOut1);
   makeOutput(this, Vec(117.69, 163.88), VCMCReceiver::Panel::Channel5_Slider3_Output);
   makeOutput(this, Vec(78.70, 163.88), VCMCReceiver::Panel::Channel5_CV3_Output);
   makeOutput(this, Vec(31.17, 131.34), VCMCReceiver::Panel::Channel4_Gate4_BitOut1);
   makeOutput(this, Vec(117.69, 131.93), VCMCReceiver::Panel::Channel4_Slider4_Output);
   makeOutput(this, Vec(78.70, 131.93), VCMCReceiver::Panel::Channel4_CV4_Output);
   makeOutput(this, Vec(31.17, 99.39), VCMCReceiver::Panel::Channel3_Gate5_BitOut1);
   makeOutput(this, Vec(117.69, 99.99), VCMCReceiver::Panel::Channel3_Slider5_Output);
   makeOutput(this, Vec(78.70, 99.99), VCMCReceiver::Panel::Channel3_CV5_Output);
   makeOutput(this, Vec(31.17, 67.45), VCMCReceiver::Panel::Channel2_Gate6_BitOut1);
   makeOutput(this, Vec(117.69, 68.04), VCMCReceiver::Panel::Channel2_Slider6_Output);
   makeOutput(this, Vec(78.70, 68.04), VCMCReceiver::Panel::Channel2_CV6_Output);
   makeOutput(this, Vec(31.17, 35.50), VCMCReceiver::Panel::Channel1_Gate7_BitOut1);
   makeOutput(this, Vec(117.69, 36.09), VCMCReceiver::Panel::Channel1_Slider7_Output);
   makeOutput(this, Vec(78.70, 36.09), VCMCReceiver::Panel::Channel1_CV7_Output);

   makeLight(this, Vec(55.36, 259.13), VCMCReceiver::Panel::RGB_Channel8_Gate_Status1);
   makeLight(this, Vec(55.36, 227.19), VCMCReceiver::Panel::RGB_Channel7_Gate1_Status1);
   makeLight(this, Vec(55.36, 195.24), VCMCReceiver::Panel::RGB_Channel6_Gate2_Status1);
   makeLight(this, Vec(55.36, 163.29), VCMCReceiver::Panel::RGB_Channel5_Gate3_Status1);
   makeLight(this, Vec(55.36, 131.34), VCMCReceiver::Panel::RGB_Channel4_Gate4_Status1);
   makeLight(this, Vec(55.36, 99.39), VCMCReceiver::Panel::RGB_Channel3_Gate5_Status1);
   makeLight(this, Vec(55.36, 67.45), VCMCReceiver::Panel::RGB_Channel2_Gate6_Status1);
   makeLight(this, Vec(55.36, 35.50), VCMCReceiver::Panel::RGB_Channel1_Gate7_Status1);

   makeDisplay(this, Vec(109.07, 286.95), 3, VCMCReceiver::Panel::Text_Clock, VCMCReceiver::Panel::RGB_Clock);

   makeMeter(this, Vec(139.04, 262.95), 5, VCMCReceiver::Panel::Value_Channel8_Slider_Strip);
   makeMeter(this, Vec(139.04, 251.31), 5, VCMCReceiver::Panel::Value_Channel8_CV_Strip);
   makeMeter(this, Vec(139.04, 231.01), 5, VCMCReceiver::Panel::Value_Channel7_Slider1_Strip);
   makeMeter(this, Vec(139.04, 219.37), 5, VCMCReceiver::Panel::Value_Channel7_CV1_Strip);
   makeMeter(this, Vec(139.04, 199.06), 5, VCMCReceiver::Panel::Value_Channel6_Slider2_Strip);
   makeMeter(this, Vec(139.04, 187.42), 5, VCMCReceiver::Panel::Value_Channel6_CV2_Strip);
   makeMeter(this, Vec(139.04, 167.11), 5, VCMCReceiver::Panel::Value_Channel5_Slider3_Strip);
   makeMeter(this, Vec(139.04, 155.47), 5, VCMCReceiver::Panel::Value_Channel5_CV3_Strip);
   makeMeter(this, Vec(139.04, 135.16), 5, VCMCReceiver::Panel::Value_Channel4_Slider4_Strip);
   makeMeter(this, Vec(139.04, 123.52), 5, VCMCReceiver::Panel::Value_Channel4_CV4_Strip);
   makeMeter(this, Vec(139.04, 103.21), 5, VCMCReceiver::Panel::Value_Channel3_Slider5_Strip);
   makeMeter(this, Vec(139.04, 91.57), 5, VCMCReceiver::Panel::Value_Channel3_CV5_Strip);
   makeMeter(this, Vec(139.04, 71.27), 5, VCMCReceiver::Panel::Value_Channel2_Slider6_Strip);
   makeMeter(this, Vec(139.04, 59.63), 5, VCMCReceiver::Panel::Value_Channel2_CV6_Strip);
   makeMeter(this, Vec(139.04, 39.32), 5, VCMCReceiver::Panel::Value_Channel1_Slider7_Strip);
   makeMeter(this, Vec(139.04, 27.68), 5, VCMCReceiver::Panel::Value_Channel1_CV7_Strip);
}

