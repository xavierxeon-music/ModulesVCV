#ifndef VCMCReceiverPanelH
#define VCMCReceiverPanelH

#include "VCMCReceiver.h"

struct VCMCReceiver::Panel
{
   enum ParamId
   {
      Connect,
      Value_Clock,
      RGB_Clock,
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
      Channel8_Gate8_BitOut1,
      Channel8_Slider8_Output,
      Channel8_CV8_Output,
      Channel7_Gate7_BitOut1,
      Channel7_Slider7_Output,
      Channel7_CV7_Output,
      Channel6_Gate6_BitOut1,
      Channel6_Slider6_Output,
      Channel6_CV6_Output,
      Channel5_Gate5_BitOut1,
      Channel5_Slider5_Output,
      Channel5_CV5_Output,
      Channel4_Gate4_BitOut1,
      Channel4_Slider4_Output,
      Channel4_CV4_Output,
      Channel3_Gate3_BitOut1,
      Channel3_Slider3_Output,
      Channel3_CV3_Output,
      Channel2_Gate2_BitOut1,
      Channel2_Slider2_Output,
      Channel2_CV2_Output,
      Channel1_Gate1_BitOut1,
      Channel1_Slider1_Output,
      Channel1_CV1_Output,
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_Channel8_Gate8_Status1,
      Green_Channel8_Gate8_Status1,
      Blue_Channel8_Gate8_Status1,
      Red_Channel8_Slider8_Status5,
      Green_Channel8_Slider8_Status5,
      Blue_Channel8_Slider8_Status5,
      Red_Channel8_Slider8_Status4,
      Green_Channel8_Slider8_Status4,
      Blue_Channel8_Slider8_Status4,
      Red_Channel8_Slider8_Status3,
      Green_Channel8_Slider8_Status3,
      Blue_Channel8_Slider8_Status3,
      Red_Channel8_Slider8_Status2,
      Green_Channel8_Slider8_Status2,
      Blue_Channel8_Slider8_Status2,
      Red_Channel8_Slider8_Status1,
      Green_Channel8_Slider8_Status1,
      Blue_Channel8_Slider8_Status1,
      Red_Channel8_CV8_Status5,
      Green_Channel8_CV8_Status5,
      Blue_Channel8_CV8_Status5,
      Red_Channel8_CV8_Status4,
      Green_Channel8_CV8_Status4,
      Blue_Channel8_CV8_Status4,
      Red_Channel8_CV8_Status3,
      Green_Channel8_CV8_Status3,
      Blue_Channel8_CV8_Status3,
      Red_Channel8_CV8_Status2,
      Green_Channel8_CV8_Status2,
      Blue_Channel8_CV8_Status2,
      Red_Channel8_CV8_Status1,
      Green_Channel8_CV8_Status1,
      Blue_Channel8_CV8_Status1,
      Red_Channel7_Gate7_Status1,
      Green_Channel7_Gate7_Status1,
      Blue_Channel7_Gate7_Status1,
      Red_Channel7_Slider7_Status5,
      Green_Channel7_Slider7_Status5,
      Blue_Channel7_Slider7_Status5,
      Red_Channel7_Slider7_Status4,
      Green_Channel7_Slider7_Status4,
      Blue_Channel7_Slider7_Status4,
      Red_Channel7_Slider7_Status3,
      Green_Channel7_Slider7_Status3,
      Blue_Channel7_Slider7_Status3,
      Red_Channel7_Slider7_Status2,
      Green_Channel7_Slider7_Status2,
      Blue_Channel7_Slider7_Status2,
      Red_Channel7_Slider7_Status1,
      Green_Channel7_Slider7_Status1,
      Blue_Channel7_Slider7_Status1,
      Red_Channel7_CV7_Status5,
      Green_Channel7_CV7_Status5,
      Blue_Channel7_CV7_Status5,
      Red_Channel7_CV7_Status4,
      Green_Channel7_CV7_Status4,
      Blue_Channel7_CV7_Status4,
      Red_Channel7_CV7_Status3,
      Green_Channel7_CV7_Status3,
      Blue_Channel7_CV7_Status3,
      Red_Channel7_CV7_Status2,
      Green_Channel7_CV7_Status2,
      Blue_Channel7_CV7_Status2,
      Red_Channel7_CV7_Status1,
      Green_Channel7_CV7_Status1,
      Blue_Channel7_CV7_Status1,
      Red_Channel6_Gate6_Status1,
      Green_Channel6_Gate6_Status1,
      Blue_Channel6_Gate6_Status1,
      Red_Channel6_Slider6_Status5,
      Green_Channel6_Slider6_Status5,
      Blue_Channel6_Slider6_Status5,
      Red_Channel6_Slider6_Status4,
      Green_Channel6_Slider6_Status4,
      Blue_Channel6_Slider6_Status4,
      Red_Channel6_Slider6_Status3,
      Green_Channel6_Slider6_Status3,
      Blue_Channel6_Slider6_Status3,
      Red_Channel6_Slider6_Status2,
      Green_Channel6_Slider6_Status2,
      Blue_Channel6_Slider6_Status2,
      Red_Channel6_Slider6_Status1,
      Green_Channel6_Slider6_Status1,
      Blue_Channel6_Slider6_Status1,
      Red_Channel6_CV6_Status5,
      Green_Channel6_CV6_Status5,
      Blue_Channel6_CV6_Status5,
      Red_Channel6_CV6_Status4,
      Green_Channel6_CV6_Status4,
      Blue_Channel6_CV6_Status4,
      Red_Channel6_CV6_Status3,
      Green_Channel6_CV6_Status3,
      Blue_Channel6_CV6_Status3,
      Red_Channel6_CV6_Status2,
      Green_Channel6_CV6_Status2,
      Blue_Channel6_CV6_Status2,
      Red_Channel6_CV6_Status1,
      Green_Channel6_CV6_Status1,
      Blue_Channel6_CV6_Status1,
      Red_Channel5_Gate5_Status1,
      Green_Channel5_Gate5_Status1,
      Blue_Channel5_Gate5_Status1,
      Red_Channel5_Slider5_Status5,
      Green_Channel5_Slider5_Status5,
      Blue_Channel5_Slider5_Status5,
      Red_Channel5_Slider5_Status4,
      Green_Channel5_Slider5_Status4,
      Blue_Channel5_Slider5_Status4,
      Red_Channel5_Slider5_Status3,
      Green_Channel5_Slider5_Status3,
      Blue_Channel5_Slider5_Status3,
      Red_Channel5_Slider5_Status2,
      Green_Channel5_Slider5_Status2,
      Blue_Channel5_Slider5_Status2,
      Red_Channel5_Slider5_Status1,
      Green_Channel5_Slider5_Status1,
      Blue_Channel5_Slider5_Status1,
      Red_Channel5_CV5_Status5,
      Green_Channel5_CV5_Status5,
      Blue_Channel5_CV5_Status5,
      Red_Channel5_CV5_Status4,
      Green_Channel5_CV5_Status4,
      Blue_Channel5_CV5_Status4,
      Red_Channel5_CV5_Status3,
      Green_Channel5_CV5_Status3,
      Blue_Channel5_CV5_Status3,
      Red_Channel5_CV5_Status2,
      Green_Channel5_CV5_Status2,
      Blue_Channel5_CV5_Status2,
      Red_Channel5_CV5_Status1,
      Green_Channel5_CV5_Status1,
      Blue_Channel5_CV5_Status1,
      Red_Channel4_Gate4_Status1,
      Green_Channel4_Gate4_Status1,
      Blue_Channel4_Gate4_Status1,
      Red_Channel4_Slider4_Status5,
      Green_Channel4_Slider4_Status5,
      Blue_Channel4_Slider4_Status5,
      Red_Channel4_Slider4_Status4,
      Green_Channel4_Slider4_Status4,
      Blue_Channel4_Slider4_Status4,
      Red_Channel4_Slider4_Status3,
      Green_Channel4_Slider4_Status3,
      Blue_Channel4_Slider4_Status3,
      Red_Channel4_Slider4_Status2,
      Green_Channel4_Slider4_Status2,
      Blue_Channel4_Slider4_Status2,
      Red_Channel4_Slider4_Status1,
      Green_Channel4_Slider4_Status1,
      Blue_Channel4_Slider4_Status1,
      Red_Channel4_CV4_Status5,
      Green_Channel4_CV4_Status5,
      Blue_Channel4_CV4_Status5,
      Red_Channel4_CV4_Status4,
      Green_Channel4_CV4_Status4,
      Blue_Channel4_CV4_Status4,
      Red_Channel4_CV4_Status3,
      Green_Channel4_CV4_Status3,
      Blue_Channel4_CV4_Status3,
      Red_Channel4_CV4_Status2,
      Green_Channel4_CV4_Status2,
      Blue_Channel4_CV4_Status2,
      Red_Channel4_CV4_Status1,
      Green_Channel4_CV4_Status1,
      Blue_Channel4_CV4_Status1,
      Red_Channel3_Gate3_Status1,
      Green_Channel3_Gate3_Status1,
      Blue_Channel3_Gate3_Status1,
      Red_Channel3_Slider3_Status5,
      Green_Channel3_Slider3_Status5,
      Blue_Channel3_Slider3_Status5,
      Red_Channel3_Slider3_Status4,
      Green_Channel3_Slider3_Status4,
      Blue_Channel3_Slider3_Status4,
      Red_Channel3_Slider3_Status3,
      Green_Channel3_Slider3_Status3,
      Blue_Channel3_Slider3_Status3,
      Red_Channel3_Slider3_Status2,
      Green_Channel3_Slider3_Status2,
      Blue_Channel3_Slider3_Status2,
      Red_Channel3_Slider3_Status1,
      Green_Channel3_Slider3_Status1,
      Blue_Channel3_Slider3_Status1,
      Red_Channel3_CV3_Status5,
      Green_Channel3_CV3_Status5,
      Blue_Channel3_CV3_Status5,
      Red_Channel3_CV3_Status4,
      Green_Channel3_CV3_Status4,
      Blue_Channel3_CV3_Status4,
      Red_Channel3_CV3_Status3,
      Green_Channel3_CV3_Status3,
      Blue_Channel3_CV3_Status3,
      Red_Channel3_CV3_Status2,
      Green_Channel3_CV3_Status2,
      Blue_Channel3_CV3_Status2,
      Red_Channel3_CV3_Status1,
      Green_Channel3_CV3_Status1,
      Blue_Channel3_CV3_Status1,
      Red_Channel2_Gate2_Status1,
      Green_Channel2_Gate2_Status1,
      Blue_Channel2_Gate2_Status1,
      Red_Channel2_Slider2_Status5,
      Green_Channel2_Slider2_Status5,
      Blue_Channel2_Slider2_Status5,
      Red_Channel2_Slider2_Status4,
      Green_Channel2_Slider2_Status4,
      Blue_Channel2_Slider2_Status4,
      Red_Channel2_Slider2_Status3,
      Green_Channel2_Slider2_Status3,
      Blue_Channel2_Slider2_Status3,
      Red_Channel2_Slider2_Status2,
      Green_Channel2_Slider2_Status2,
      Blue_Channel2_Slider2_Status2,
      Red_Channel2_Slider2_Status1,
      Green_Channel2_Slider2_Status1,
      Blue_Channel2_Slider2_Status1,
      Red_Channel2_CV2_Status5,
      Green_Channel2_CV2_Status5,
      Blue_Channel2_CV2_Status5,
      Red_Channel2_CV2_Status4,
      Green_Channel2_CV2_Status4,
      Blue_Channel2_CV2_Status4,
      Red_Channel2_CV2_Status3,
      Green_Channel2_CV2_Status3,
      Blue_Channel2_CV2_Status3,
      Red_Channel2_CV2_Status2,
      Green_Channel2_CV2_Status2,
      Blue_Channel2_CV2_Status2,
      Red_Channel2_CV2_Status1,
      Green_Channel2_CV2_Status1,
      Blue_Channel2_CV2_Status1,
      Red_Channel1_Gate1_Status1,
      Green_Channel1_Gate1_Status1,
      Blue_Channel1_Gate1_Status1,
      Red_Channel1_Slider1_Status5,
      Green_Channel1_Slider1_Status5,
      Blue_Channel1_Slider1_Status5,
      Red_Channel1_Slider1_Status4,
      Green_Channel1_Slider1_Status4,
      Blue_Channel1_Slider1_Status4,
      Red_Channel1_Slider1_Status3,
      Green_Channel1_Slider1_Status3,
      Blue_Channel1_Slider1_Status3,
      Red_Channel1_Slider1_Status2,
      Green_Channel1_Slider1_Status2,
      Blue_Channel1_Slider1_Status2,
      Red_Channel1_Slider1_Status1,
      Green_Channel1_Slider1_Status1,
      Blue_Channel1_Slider1_Status1,
      Red_Channel1_CV1_Status5,
      Green_Channel1_CV1_Status5,
      Blue_Channel1_CV1_Status5,
      Red_Channel1_CV1_Status4,
      Green_Channel1_CV1_Status4,
      Blue_Channel1_CV1_Status4,
      Red_Channel1_CV1_Status3,
      Green_Channel1_CV1_Status3,
      Blue_Channel1_CV1_Status3,
      Red_Channel1_CV1_Status2,
      Green_Channel1_CV1_Status2,
      Blue_Channel1_CV1_Status2,
      Red_Channel1_CV1_Status1,
      Green_Channel1_CV1_Status1,
      Blue_Channel1_CV1_Status1,
      Red_Connect,
      Green_Connect,
      Blue_Connect,
      LIGHTS_LEN
   };

};

#endif // NOT VCMCReceiverPanelH
