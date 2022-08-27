#ifndef VCMCReceiverPanelH
#define VCMCReceiverPanelH

#include "VCMCReceiver.h"

#include <SvinCommon.h>
#include <SvinButtonLED.h>
#include <SvinLED.h>
#include <SvinLightMeter.h>
#include <SvinOutput.h>

struct VCMCReceiver::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Connect = 0,
      // knobs
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
      // lcds
      LIGHTS_LEN = 51
   };

};

#endif // NOT VCMCReceiverPanelH
