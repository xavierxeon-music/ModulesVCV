#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <SvinMaster.h>

void VCMCReceiver::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configOutput(Panel::External_B, "External_B");
   configOutput(Panel::External_A, "External_A");
   configOutput(Panel::Gate, "Gate");
   configOutput(Panel::CV, "CV");

   configMeter(Panel::Value_External_B, "External_B");
   configMeter(Panel::Value_External_A, "External_A");
   configMeter(Panel::Value_Slider_Channel18, "Slider_Channel18");
   configMeter(Panel::Value_Slider_Channel17, "Slider_Channel17");
   configMeter(Panel::Value_Slider_Channel6, "Slider_Channel6");
   configMeter(Panel::Value_Slider_Channel5, "Slider_Channel5");
   configMeter(Panel::Value_Slider_Channel4, "Slider_Channel4");
   configMeter(Panel::Value_Slider_Channel3, "Slider_Channel3");
   configMeter(Panel::Value_Slider_Channel2, "Slider_Channel2");
   configMeter(Panel::Value_Slider_Channel1, "Slider_Channel1");
   configMeter(Panel::Value_CV_Channel18, "CV_Channel18");
   configMeter(Panel::Value_CV_Channel17, "CV_Channel17");
   configMeter(Panel::Value_CV_Channel6, "CV_Channel6");
   configMeter(Panel::Value_CV_Channel5, "CV_Channel5");
   configMeter(Panel::Value_CV_Channel4, "CV_Channel4");
   configMeter(Panel::Value_CV_Channel3, "CV_Channel3");
   configMeter(Panel::Value_CV_Channel2, "CV_Channel2");
   configMeter(Panel::Value_CV_Channel1, "CV_Channel1");
}

void VCMCReceiverWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/Hardware/VCMCReceiver.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(59.87, 360.10), VCMCReceiver::Panel::Connect, VCMCReceiver::Panel::RGB_Connect);

   makeOutput(this, Vec(65.83, 322.31), VCMCReceiver::Panel::External_B, false);
   makeOutput(this, Vec(65.83, 290.93), VCMCReceiver::Panel::External_A, false);
   makeOutput(this, Vec(66.21, 243.36), VCMCReceiver::Panel::Gate, true);
   makeOutput(this, Vec(64.16, 140.05), VCMCReceiver::Panel::CV, true);

   makeLED(this, Vec(76.57, 214.65), VCMCReceiver::Panel::RGB_Latch_Channel8);
   makeLED(this, Vec(67.69, 214.65), VCMCReceiver::Panel::RGB_Latch_Channel7);
   makeLED(this, Vec(58.82, 214.65), VCMCReceiver::Panel::RGB_Latch_Channel6);
   makeLED(this, Vec(49.95, 214.65), VCMCReceiver::Panel::RGB_Latch_Channel5);
   makeLED(this, Vec(41.07, 214.65), VCMCReceiver::Panel::RGB_Latch_Channel4);
   makeLED(this, Vec(32.20, 214.65), VCMCReceiver::Panel::RGB_Latch_Channel3);
   makeLED(this, Vec(23.32, 214.65), VCMCReceiver::Panel::RGB_Latch_Channe21);
   makeLED(this, Vec(14.45, 214.65), VCMCReceiver::Panel::RGB_Latch_Channel1);
   makeLED(this, Vec(76.57, 190.33), VCMCReceiver::Panel::RGB_Gate_Channel8);
   makeLED(this, Vec(67.69, 190.33), VCMCReceiver::Panel::RGB_Gate_Channel7);
   makeLED(this, Vec(58.82, 190.33), VCMCReceiver::Panel::RGB_Gate_Channel6);
   makeLED(this, Vec(49.95, 190.33), VCMCReceiver::Panel::RGB_Gate_Channel5);
   makeLED(this, Vec(41.07, 190.33), VCMCReceiver::Panel::RGB_Gate_Channel4);
   makeLED(this, Vec(32.20, 190.33), VCMCReceiver::Panel::RGB_Gate_Channel3);
   makeLED(this, Vec(23.32, 190.33), VCMCReceiver::Panel::RGB_Gate_Channe21);
   makeLED(this, Vec(14.45, 190.33), VCMCReceiver::Panel::RGB_Gate_Channel1);

   makeMeter(this, Vec(43.75, 309.45), 5, VCMCReceiver::Panel::Value_External_B);
   makeMeter(this, Vec(43.42, 277.75), 5, VCMCReceiver::Panel::Value_External_A);
   makeMeter(this, Vec(72.34, 91.15), 5, VCMCReceiver::Panel::Value_Slider_Channel18);
   makeMeter(this, Vec(63.43, 91.15), 5, VCMCReceiver::Panel::Value_Slider_Channel17);
   makeMeter(this, Vec(54.53, 91.15), 5, VCMCReceiver::Panel::Value_Slider_Channel6);
   makeMeter(this, Vec(45.62, 91.15), 5, VCMCReceiver::Panel::Value_Slider_Channel5);
   makeMeter(this, Vec(36.72, 91.15), 5, VCMCReceiver::Panel::Value_Slider_Channel4);
   makeMeter(this, Vec(27.81, 91.15), 5, VCMCReceiver::Panel::Value_Slider_Channel3);
   makeMeter(this, Vec(18.91, 91.15), 5, VCMCReceiver::Panel::Value_Slider_Channel2);
   makeMeter(this, Vec(10.00, 91.15), 5, VCMCReceiver::Panel::Value_Slider_Channel1);
   makeMeter(this, Vec(72.34, 48.29), 5, VCMCReceiver::Panel::Value_CV_Channel18);
   makeMeter(this, Vec(63.43, 48.29), 5, VCMCReceiver::Panel::Value_CV_Channel17);
   makeMeter(this, Vec(54.53, 48.29), 5, VCMCReceiver::Panel::Value_CV_Channel6);
   makeMeter(this, Vec(45.62, 48.29), 5, VCMCReceiver::Panel::Value_CV_Channel5);
   makeMeter(this, Vec(36.72, 48.29), 5, VCMCReceiver::Panel::Value_CV_Channel4);
   makeMeter(this, Vec(27.81, 48.29), 5, VCMCReceiver::Panel::Value_CV_Channel3);
   makeMeter(this, Vec(18.91, 48.29), 5, VCMCReceiver::Panel::Value_CV_Channel2);
   makeMeter(this, Vec(10.00, 48.29), 5, VCMCReceiver::Panel::Value_CV_Channel1);
}

