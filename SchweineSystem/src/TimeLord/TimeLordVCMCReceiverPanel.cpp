#include "TimeLordVCMCReceiverPanel.h"
#include "TimeLordVCMCReceiver.h"

#include <SvinOrigin.h>

void TimeLordVCMCReceiver::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configOutput(Panel::External_B, "External_B");
   configOutput(Panel::External_A, "External_A");
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
}

void TimeLordVCMCReceiverWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/TimeLord/TimeLordVCMCReceiver.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(113.83, 355.94), TimeLordVCMCReceiver::Panel::Connect, TimeLordVCMCReceiver::Panel::RGB_Connect);

   makeOutput(this, Vec(71.25, 355.83), TimeLordVCMCReceiver::Panel::External_B, false);
   makeOutput(this, Vec(27.28, 355.58), TimeLordVCMCReceiver::Panel::External_A, false);
   makeOutput(this, Vec(32.19, 311.65), TimeLordVCMCReceiver::Panel::Channel8_Gate_BitOut1, false);
   makeOutput(this, Vec(114.88, 311.65), TimeLordVCMCReceiver::Panel::Channel8_Slider_Output, false);
   makeOutput(this, Vec(73.72, 311.65), TimeLordVCMCReceiver::Panel::Channel8_CV_Output, false);
   makeOutput(this, Vec(32.83, 276.27), TimeLordVCMCReceiver::Panel::Channel7_Gate1_BitOut1, false);
   makeOutput(this, Vec(115.52, 276.27), TimeLordVCMCReceiver::Panel::Channel7_Slider1_Output, false);
   makeOutput(this, Vec(74.36, 276.27), TimeLordVCMCReceiver::Panel::Channel7_CV1_Output, false);
   makeOutput(this, Vec(32.83, 240.90), TimeLordVCMCReceiver::Panel::Channel6_Gate2_BitOut1, false);
   makeOutput(this, Vec(115.52, 240.90), TimeLordVCMCReceiver::Panel::Channel6_Slider2_Output, false);
   makeOutput(this, Vec(74.36, 240.90), TimeLordVCMCReceiver::Panel::Channel6_CV2_Output, false);
   makeOutput(this, Vec(32.83, 205.53), TimeLordVCMCReceiver::Panel::Channel5_Gate3_BitOut1, false);
   makeOutput(this, Vec(115.52, 205.53), TimeLordVCMCReceiver::Panel::Channel5_Slider3_Output, false);
   makeOutput(this, Vec(74.36, 205.53), TimeLordVCMCReceiver::Panel::Channel5_CV3_Output, false);
   makeOutput(this, Vec(32.83, 170.15), TimeLordVCMCReceiver::Panel::Channel4_Gate4_BitOut1, false);
   makeOutput(this, Vec(115.52, 170.15), TimeLordVCMCReceiver::Panel::Channel4_Slider4_Output, false);
   makeOutput(this, Vec(74.36, 170.15), TimeLordVCMCReceiver::Panel::Channel4_CV4_Output, false);
   makeOutput(this, Vec(32.83, 134.78), TimeLordVCMCReceiver::Panel::Channel3_Gate5_BitOut1, false);
   makeOutput(this, Vec(115.52, 134.78), TimeLordVCMCReceiver::Panel::Channel3_Slider5_Output, false);
   makeOutput(this, Vec(74.36, 134.78), TimeLordVCMCReceiver::Panel::Channel3_CV5_Output, false);
   makeOutput(this, Vec(32.83, 99.41), TimeLordVCMCReceiver::Panel::Channel2_Gate6_BitOut1, false);
   makeOutput(this, Vec(115.52, 99.41), TimeLordVCMCReceiver::Panel::Channel2_Slider6_Output, false);
   makeOutput(this, Vec(74.36, 99.41), TimeLordVCMCReceiver::Panel::Channel2_CV6_Output, false);
   makeOutput(this, Vec(32.83, 64.03), TimeLordVCMCReceiver::Panel::Channel1_Gate7_BitOut1, false);
   makeOutput(this, Vec(115.52, 64.03), TimeLordVCMCReceiver::Panel::Channel1_Slider7_Output, false);
   makeOutput(this, Vec(74.36, 64.03), TimeLordVCMCReceiver::Panel::Channel1_CV7_Output, false);

   makeLED(this, Vec(53.38, 311.65), TimeLordVCMCReceiver::Panel::RGB_Channel8_Gate_Status1);
   makeLED(this, Vec(54.02, 276.27), TimeLordVCMCReceiver::Panel::RGB_Channel7_Gate1_Status1);
   makeLED(this, Vec(54.02, 240.90), TimeLordVCMCReceiver::Panel::RGB_Channel6_Gate2_Status1);
   makeLED(this, Vec(54.02, 205.53), TimeLordVCMCReceiver::Panel::RGB_Channel5_Gate3_Status1);
   makeLED(this, Vec(54.02, 170.15), TimeLordVCMCReceiver::Panel::RGB_Channel4_Gate4_Status1);
   makeLED(this, Vec(54.02, 134.78), TimeLordVCMCReceiver::Panel::RGB_Channel3_Gate5_Status1);
   makeLED(this, Vec(54.02, 99.41), TimeLordVCMCReceiver::Panel::RGB_Channel2_Gate6_Status1);
   makeLED(this, Vec(54.02, 64.03), TimeLordVCMCReceiver::Panel::RGB_Channel1_Gate7_Status1);

   makeMeter(this, Vec(87.18, 342.97), 5, TimeLordVCMCReceiver::Panel::Value_External_B);
   makeMeter(this, Vec(43.87, 342.41), 5, TimeLordVCMCReceiver::Panel::Value_External_A);
   makeMeter(this, Vec(131.70, 298.65), 5, TimeLordVCMCReceiver::Panel::Value_Channel8_Slider_Strip);
   makeMeter(this, Vec(90.54, 298.65), 5, TimeLordVCMCReceiver::Panel::Value_Channel8_CV_Strip);
   makeMeter(this, Vec(132.34, 263.27), 5, TimeLordVCMCReceiver::Panel::Value_Channel7_Slider1_Strip);
   makeMeter(this, Vec(91.18, 263.27), 5, TimeLordVCMCReceiver::Panel::Value_Channel7_CV1_Strip);
   makeMeter(this, Vec(132.34, 227.90), 5, TimeLordVCMCReceiver::Panel::Value_Channel6_Slider2_Strip);
   makeMeter(this, Vec(91.18, 227.90), 5, TimeLordVCMCReceiver::Panel::Value_Channel6_CV2_Strip);
   makeMeter(this, Vec(132.34, 192.53), 5, TimeLordVCMCReceiver::Panel::Value_Channel5_Slider3_Strip);
   makeMeter(this, Vec(91.18, 192.53), 5, TimeLordVCMCReceiver::Panel::Value_Channel5_CV3_Strip);
   makeMeter(this, Vec(132.34, 157.15), 5, TimeLordVCMCReceiver::Panel::Value_Channel4_Slider4_Strip);
   makeMeter(this, Vec(91.18, 157.15), 5, TimeLordVCMCReceiver::Panel::Value_Channel4_CV4_Strip);
   makeMeter(this, Vec(132.34, 121.78), 5, TimeLordVCMCReceiver::Panel::Value_Channel3_Slider5_Strip);
   makeMeter(this, Vec(91.18, 121.78), 5, TimeLordVCMCReceiver::Panel::Value_Channel3_CV5_Strip);
   makeMeter(this, Vec(132.34, 86.41), 5, TimeLordVCMCReceiver::Panel::Value_Channel2_Slider6_Strip);
   makeMeter(this, Vec(91.18, 86.41), 5, TimeLordVCMCReceiver::Panel::Value_Channel2_CV6_Strip);
   makeMeter(this, Vec(132.34, 51.03), 5, TimeLordVCMCReceiver::Panel::Value_Channel1_Slider7_Strip);
   makeMeter(this, Vec(91.18, 51.03), 5, TimeLordVCMCReceiver::Panel::Value_Channel1_CV7_Strip);
}
