#ifndef VCMCReceiverHPP
#define VCMCReceiverHPP

#include "VCMCReceiver.h"

#include <SvinOrigin.h>

struct VCMCReceiver::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Connect = 0,
      // knobs
      // sliders
      PARAMS_LEN = 1
   };

   enum DisplayId
   {
      // lcd
      // oled
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      Value_External_B = 0,
      Value_External_A = 1,
      Value_Slider_Channel8 = 2,
      Value_Slider_Channel7 = 3,
      Value_Slider_Channel6 = 4,
      Value_Slider_Channel5 = 5,
      Value_Slider_Channel4 = 6,
      Value_Slider_Channel3 = 7,
      Value_Slider_Channel2 = 8,
      Value_Slider_Channel1 = 9,
      Value_CV_Channel8 = 10,
      Value_CV_Channel7 = 11,
      Value_CV_Channel6 = 12,
      Value_CV_Channel5 = 13,
      Value_CV_Channel4 = 14,
      Value_CV_Channel3 = 15,
      Value_CV_Channel2 = 16,
      Value_CV_Channel1 = 17,
      METERS_LEN = 18
   };

   enum InputId
   {
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      External_B = 0,
      External_A = 1,
      CV = 2,
      Gate = 3,
      OUTPUTS_LEN = 4
   };

   enum LightId
   {
      // leds
      RGB_Latch_Channel8 = 0,
      RGB_Latch_Channel7 = 3,
      RGB_Latch_Channel6 = 6,
      RGB_Latch_Channel5 = 9,
      RGB_Latch_Channel4 = 12,
      RGB_Latch_Channel3 = 15,
      RGB_Latch_Channel2 = 18,
      RGB_Latch_Channel1 = 21,
      RGB_Gate_Channel8 = 24,
      RGB_Gate_Channel7 = 27,
      RGB_Gate_Channel6 = 30,
      RGB_Gate_Channel5 = 33,
      RGB_Gate_Channel4 = 36,
      RGB_Gate_Channel3 = 39,
      RGB_Gate_Channel2 = 42,
      RGB_Gate_Channel1 = 45,
      // ledbuttons
      RGB_Connect = 48,
      // sliders
      LIGHTS_LEN = 51
   };

};

void VCMCReceiver::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configOutput(Panel::External_B, "External_B");
   configOutput(Panel::External_A, "External_A");
   configOutput(Panel::CV, "CV");
   configOutput(Panel::Gate, "Gate");
}

void VCMCReceiverWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Hardware/VCMCReceiver.svg");
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
   makeLED(this, Vec(22.94, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel2);
   makeLED(this, Vec(14.06, 77.76), VCMCReceiver::Panel::RGB_Latch_Channel1);
   makeLED(this, Vec(76.18, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel8);
   makeLED(this, Vec(67.31, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel7);
   makeLED(this, Vec(58.43, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel6);
   makeLED(this, Vec(49.56, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel5);
   makeLED(this, Vec(40.69, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel4);
   makeLED(this, Vec(31.81, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel3);
   makeLED(this, Vec(22.94, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel2);
   makeLED(this, Vec(14.06, 53.44), VCMCReceiver::Panel::RGB_Gate_Channel1);

   makeMeter(this, Vec(43.75, 309.45), 5, VCMCReceiver::Panel::Value_External_B);
   makeMeter(this, Vec(43.42, 277.75), 5, VCMCReceiver::Panel::Value_External_A);
   makeMeter(this, Vec(73.29, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel8);
   makeMeter(this, Vec(64.38, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel7);
   makeMeter(this, Vec(55.48, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel6);
   makeMeter(this, Vec(46.57, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel5);
   makeMeter(this, Vec(37.67, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel4);
   makeMeter(this, Vec(28.76, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel3);
   makeMeter(this, Vec(19.86, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel2);
   makeMeter(this, Vec(10.95, 190.90), 5, VCMCReceiver::Panel::Value_Slider_Channel1);
   makeMeter(this, Vec(73.29, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel8);
   makeMeter(this, Vec(64.38, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel7);
   makeMeter(this, Vec(55.48, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel6);
   makeMeter(this, Vec(46.57, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel5);
   makeMeter(this, Vec(37.67, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel4);
   makeMeter(this, Vec(28.76, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel3);
   makeMeter(this, Vec(19.86, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel2);
   makeMeter(this, Vec(10.95, 148.05), 5, VCMCReceiver::Panel::Value_CV_Channel1);
}

Model* modelVCMCReceiver = Svin::Origin::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");

#endif // NOT VCMCReceiverHPP
