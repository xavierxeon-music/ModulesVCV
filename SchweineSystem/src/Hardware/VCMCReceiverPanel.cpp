#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <SvinMaster.h>

void VCMCReceiver::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configOutput(Panel::External_B, "External_B");
   configOutput(Panel::External_A, "External_A");
   configOutput(Panel::CV, "CV");
   configOutput(Panel::Gate, "Gate");

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
   makeOutput(this, Vec(65.12, 239.81), VCMCReceiver::Panel::CV, true);
   makeOutput(this, Vec(65.83, 106.47), VCMCReceiver::Panel::Gate, true);

   makeLED(this, Vec(76.18, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel8);
   makeLED(this, Vec(67.31, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel7);
   makeLED(this, Vec(58.43, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel6);
   makeLED(this, Vec(49.56, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel5);
   makeLED(this, Vec(40.69, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel4);
   makeLED(this, Vec(31.81, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel3);
   makeLED(this, Vec(22.94, 77.76), VCMCReceiver::Panel::RGB_Latch_Channe21);
   makeLED(this, Vec(14.06, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel1);
   makeLED(this, Vec(76.18, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel8);
   makeLED(this, Vec(67.31, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel7);
   makeLED(this, Vec(58.43, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel6);
   makeLED(this, Vec(49.56, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel5);
   makeLED(this, Vec(40.69, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel4);
   makeLED(this, Vec(31.81, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel3);
   makeLED(this, Vec(22.94, 53.44), VCMCReceiver::Panel::RGB_Gate_Channe21);
   makeLED(this, Vec(14.06, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel1);

   makeMeter(this, Vec(43.75, 309.45), 5, VCMCReceiver::Panel::Value_External_B);
   makeMeter(this, Vec(43.42, 277.75), 5, VCMCReceiver::Panel::Value_External_A);
   makeMeter(this, Vec(73.29, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel18);
   makeMeter(this, Vec(64.38, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel17);
   makeMeter(this, Vec(55.48, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel6);
   makeMeter(this, Vec(46.57, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel5);
   makeMeter(this, Vec(37.67, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel4);
   makeMeter(this, Vec(28.76, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel3);
   makeMeter(this, Vec(19.86, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel2);
   makeMeter(this, Vec(10.95, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel1);
   makeMeter(this, Vec(73.29, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel18);
   makeMeter(this, Vec(64.38, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel17);
   makeMeter(this, Vec(55.48, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel6);
   makeMeter(this, Vec(46.57, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel5);
   makeMeter(this, Vec(37.67, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel4);
   makeMeter(this, Vec(28.76, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel3);
   makeMeter(this, Vec(19.86, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel2);
   makeMeter(this, Vec(10.95, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel1);
}

