#ifndef VCMCReceiverPanelH
#define VCMCReceiverPanelH

#include "VCMCReceiver.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>
#include <SchweineSystemLight.h>
#include <SchweineSystemLightMeter.h>

struct VCMCReceiver::Panel
{
   enum ParamId
   {
      Connect,
      Value_Clock,
      Value_Channel8_Slider_Strip,
      Value_Channel8_CV_Strip,
      Value_Channel7_Slider1_Strip,
      Value_Channel7_CV1_Strip,
      Value_Channel6_Slider2_Strip,
      Value_Channel6_CV2_Strip,
      Value_Channel5_Slider3_Strip,
      Value_Channel5_CV3_Strip,
      Value_Channel4_Slider4_Strip,
      Value_Channel4_CV4_Strip,
      Value_Channel3_Slider5_Strip,
      Value_Channel3_CV5_Strip,
      Value_Channel2_Slider6_Strip,
      Value_Channel2_CV6_Strip,
      Value_Channel1_Slider7_Strip,
      Value_Channel1_CV7_Strip,
      PARAMS_LEN
   };

   enum InputId
   {
      ClockOverride,
      INPUTS_LEN
   };

   enum OutputId
   {
      Reset,
      Clock,
      Channel8_Gate_BitOut1,
      Channel8_Slider_Output,
      Channel8_CV_Output,
      Channel7_Gate1_BitOut1,
      Channel7_Slider1_Output,
      Channel7_CV1_Output,
      Channel6_Gate2_BitOut1,
      Channel6_Slider2_Output,
      Channel6_CV2_Output,
      Channel5_Gate3_BitOut1,
      Channel5_Slider3_Output,
      Channel5_CV3_Output,
      Channel4_Gate4_BitOut1,
      Channel4_Slider4_Output,
      Channel4_CV4_Output,
      Channel3_Gate5_BitOut1,
      Channel3_Slider5_Output,
      Channel3_CV5_Output,
      Channel2_Gate6_BitOut1,
      Channel2_Slider6_Output,
      Channel2_CV6_Output,
      Channel1_Gate7_BitOut1,
      Channel1_Slider7_Output,
      Channel1_CV7_Output,
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_Channel8_Gate_Status1,
      Green_Channel8_Gate_Status1,
      Blue_Channel8_Gate_Status1,
      Red_Channel7_Gate1_Status1,
      Green_Channel7_Gate1_Status1,
      Blue_Channel7_Gate1_Status1,
      Red_Channel6_Gate2_Status1,
      Green_Channel6_Gate2_Status1,
      Blue_Channel6_Gate2_Status1,
      Red_Channel5_Gate3_Status1,
      Green_Channel5_Gate3_Status1,
      Blue_Channel5_Gate3_Status1,
      Red_Channel4_Gate4_Status1,
      Green_Channel4_Gate4_Status1,
      Blue_Channel4_Gate4_Status1,
      Red_Channel3_Gate5_Status1,
      Green_Channel3_Gate5_Status1,
      Blue_Channel3_Gate5_Status1,
      Red_Channel2_Gate6_Status1,
      Green_Channel2_Gate6_Status1,
      Blue_Channel2_Gate6_Status1,
      Red_Channel1_Gate7_Status1,
      Green_Channel1_Gate7_Status1,
      Blue_Channel1_Gate7_Status1,
      Red_Connect,
      Green_Connect,
      Blue_Connect,
      Red_Clock,
      Green_Clock,
      Blue_Clock,
      LIGHTS_LEN
   };

   Panel();
};

#endif // NOT VCMCReceiverPanelH
