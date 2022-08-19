#ifndef VCMCReceiverPanelH
#define VCMCReceiverPanelH

#include "VCMCReceiver.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemLightMeter.h>

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
      Value_Channel8_Slider_Strip = 2,
      Value_Channel8_CV_Strip = 3,
      Value_Channel7_Slider1_Strip = 4,
      Value_Channel7_CV1_Strip = 5,
      Value_Channel6_Slider2_Strip = 6,
      Value_Channel6_CV2_Strip = 7,
      Value_Channel5_Slider3_Strip = 8,
      Value_Channel5_CV3_Strip = 9,
      Value_Channel4_Slider4_Strip = 10,
      Value_Channel4_CV4_Strip = 11,
      Value_Channel3_Slider5_Strip = 12,
      Value_Channel3_CV5_Strip = 13,
      Value_Channel2_Slider6_Strip = 14,
      Value_Channel2_CV6_Strip = 15,
      Value_Channel1_Slider7_Strip = 16,
      Value_Channel1_CV7_Strip = 17,
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
      Channel8_Gate_BitOut1 = 2,
      Channel8_Slider_Output = 3,
      Channel8_CV_Output = 4,
      Channel7_Gate1_BitOut1 = 5,
      Channel7_Slider1_Output = 6,
      Channel7_CV1_Output = 7,
      Channel6_Gate2_BitOut1 = 8,
      Channel6_Slider2_Output = 9,
      Channel6_CV2_Output = 10,
      Channel5_Gate3_BitOut1 = 11,
      Channel5_Slider3_Output = 12,
      Channel5_CV3_Output = 13,
      Channel4_Gate4_BitOut1 = 14,
      Channel4_Slider4_Output = 15,
      Channel4_CV4_Output = 16,
      Channel3_Gate5_BitOut1 = 17,
      Channel3_Slider5_Output = 18,
      Channel3_CV5_Output = 19,
      Channel2_Gate6_BitOut1 = 20,
      Channel2_Slider6_Output = 21,
      Channel2_CV6_Output = 22,
      Channel1_Gate7_BitOut1 = 23,
      Channel1_Slider7_Output = 24,
      Channel1_CV7_Output = 25,
      OUTPUTS_LEN = 26
   };

   enum LightId
   {
      // leds
      RGB_Channel8_Gate_Status1 = 0,
      RGB_Channel7_Gate1_Status1 = 3,
      RGB_Channel6_Gate2_Status1 = 6,
      RGB_Channel5_Gate3_Status1 = 9,
      RGB_Channel4_Gate4_Status1 = 12,
      RGB_Channel3_Gate5_Status1 = 15,
      RGB_Channel2_Gate6_Status1 = 18,
      RGB_Channel1_Gate7_Status1 = 21,
      // ledbuttons
      RGB_Connect = 24,
      // lcds
      LIGHTS_LEN = 27
   };

};

#endif // NOT VCMCReceiverPanelH
