#ifndef TimeLordServerPanelH
#define TimeLordServerPanelH

#include "TimeLordServer.h"

struct TimeLordServer::Panel
{
   enum ParamId
   {
      PARAMS_LEN
   };

   enum InputId
   {
      Reset,
      Clock,
      INPUTS_LEN
   };

   enum OutputId
   {
      Channel16_Output,
      Channel8_Output,
      Channel15_Output,
      Channel7_Output,
      Channel14_Output,
      Channel6_Output,
      Channel13_Output,
      Channel5_Output,
      Channel12_Output,
      Channel4_Output,
      Channel11_Output,
      Channel3_Output,
      Channel10_Output,
      Channel2_Output,
      Channel9_Output,
      Channel1_Output,
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_LoadB,
      Green_LoadB,
      Blue_LoadB,
      Red_LoadA,
      Green_LoadA,
      Blue_LoadA,
      Red_Channel16_Status5,
      Green_Channel16_Status5,
      Blue_Channel16_Status5,
      Red_Channel16_Status4,
      Green_Channel16_Status4,
      Blue_Channel16_Status4,
      Red_Channel16_Status3,
      Green_Channel16_Status3,
      Blue_Channel16_Status3,
      Red_Channel16_Status2,
      Green_Channel16_Status2,
      Blue_Channel16_Status2,
      Red_Channel16_Status1,
      Green_Channel16_Status1,
      Blue_Channel16_Status1,
      Red_Channel8_Status5,
      Green_Channel8_Status5,
      Blue_Channel8_Status5,
      Red_Channel8_Status4,
      Green_Channel8_Status4,
      Blue_Channel8_Status4,
      Red_Channel8_Status3,
      Green_Channel8_Status3,
      Blue_Channel8_Status3,
      Red_Channel8_Status2,
      Green_Channel8_Status2,
      Blue_Channel8_Status2,
      Red_Channel8_Status1,
      Green_Channel8_Status1,
      Blue_Channel8_Status1,
      Red_Channel15_Status5,
      Green_Channel15_Status5,
      Blue_Channel15_Status5,
      Red_Channel15_Status4,
      Green_Channel15_Status4,
      Blue_Channel15_Status4,
      Red_Channel15_Status3,
      Green_Channel15_Status3,
      Blue_Channel15_Status3,
      Red_Channel15_Status2,
      Green_Channel15_Status2,
      Blue_Channel15_Status2,
      Red_Channel15_Status1,
      Green_Channel15_Status1,
      Blue_Channel15_Status1,
      Red_Channel7_Status5,
      Green_Channel7_Status5,
      Blue_Channel7_Status5,
      Red_Channel7_Status4,
      Green_Channel7_Status4,
      Blue_Channel7_Status4,
      Red_Channel7_Status3,
      Green_Channel7_Status3,
      Blue_Channel7_Status3,
      Red_Channel7_Status2,
      Green_Channel7_Status2,
      Blue_Channel7_Status2,
      Red_Channel7_Status1,
      Green_Channel7_Status1,
      Blue_Channel7_Status1,
      Red_Channel14_Status5,
      Green_Channel14_Status5,
      Blue_Channel14_Status5,
      Red_Channel14_Status4,
      Green_Channel14_Status4,
      Blue_Channel14_Status4,
      Red_Channel14_Status3,
      Green_Channel14_Status3,
      Blue_Channel14_Status3,
      Red_Channel14_Status2,
      Green_Channel14_Status2,
      Blue_Channel14_Status2,
      Red_Channel14_Status1,
      Green_Channel14_Status1,
      Blue_Channel14_Status1,
      Red_Channel6_Status5,
      Green_Channel6_Status5,
      Blue_Channel6_Status5,
      Red_Channel6_Status4,
      Green_Channel6_Status4,
      Blue_Channel6_Status4,
      Red_Channel6_Status3,
      Green_Channel6_Status3,
      Blue_Channel6_Status3,
      Red_Channel6_Status2,
      Green_Channel6_Status2,
      Blue_Channel6_Status2,
      Red_Channel6_Status1,
      Green_Channel6_Status1,
      Blue_Channel6_Status1,
      Red_Channel13_Status5,
      Green_Channel13_Status5,
      Blue_Channel13_Status5,
      Red_Channel13_Status4,
      Green_Channel13_Status4,
      Blue_Channel13_Status4,
      Red_Channel13_Status3,
      Green_Channel13_Status3,
      Blue_Channel13_Status3,
      Red_Channel13_Status2,
      Green_Channel13_Status2,
      Blue_Channel13_Status2,
      Red_Channel13_Status1,
      Green_Channel13_Status1,
      Blue_Channel13_Status1,
      Red_Channel5_Status5,
      Green_Channel5_Status5,
      Blue_Channel5_Status5,
      Red_Channel5_Status4,
      Green_Channel5_Status4,
      Blue_Channel5_Status4,
      Red_Channel5_Status3,
      Green_Channel5_Status3,
      Blue_Channel5_Status3,
      Red_Channel5_Status2,
      Green_Channel5_Status2,
      Blue_Channel5_Status2,
      Red_Channel5_Status1,
      Green_Channel5_Status1,
      Blue_Channel5_Status1,
      Red_Channel12_Status5,
      Green_Channel12_Status5,
      Blue_Channel12_Status5,
      Red_Channel12_Status4,
      Green_Channel12_Status4,
      Blue_Channel12_Status4,
      Red_Channel12_Status3,
      Green_Channel12_Status3,
      Blue_Channel12_Status3,
      Red_Channel12_Status2,
      Green_Channel12_Status2,
      Blue_Channel12_Status2,
      Red_Channel12_Status1,
      Green_Channel12_Status1,
      Blue_Channel12_Status1,
      Red_Channel4_Status5,
      Green_Channel4_Status5,
      Blue_Channel4_Status5,
      Red_Channel4_Status4,
      Green_Channel4_Status4,
      Blue_Channel4_Status4,
      Red_Channel4_Status3,
      Green_Channel4_Status3,
      Blue_Channel4_Status3,
      Red_Channel4_Status2,
      Green_Channel4_Status2,
      Blue_Channel4_Status2,
      Red_Channel4_Status1,
      Green_Channel4_Status1,
      Blue_Channel4_Status1,
      Red_Channel11_Status5,
      Green_Channel11_Status5,
      Blue_Channel11_Status5,
      Red_Channel11_Status4,
      Green_Channel11_Status4,
      Blue_Channel11_Status4,
      Red_Channel11_Status3,
      Green_Channel11_Status3,
      Blue_Channel11_Status3,
      Red_Channel11_Status2,
      Green_Channel11_Status2,
      Blue_Channel11_Status2,
      Red_Channel11_Status1,
      Green_Channel11_Status1,
      Blue_Channel11_Status1,
      Red_Channel3_Status5,
      Green_Channel3_Status5,
      Blue_Channel3_Status5,
      Red_Channel3_Status4,
      Green_Channel3_Status4,
      Blue_Channel3_Status4,
      Red_Channel3_Status3,
      Green_Channel3_Status3,
      Blue_Channel3_Status3,
      Red_Channel3_Status2,
      Green_Channel3_Status2,
      Blue_Channel3_Status2,
      Red_Channel3_Status1,
      Green_Channel3_Status1,
      Blue_Channel3_Status1,
      Red_Channel10_Status5,
      Green_Channel10_Status5,
      Blue_Channel10_Status5,
      Red_Channel10_Status4,
      Green_Channel10_Status4,
      Blue_Channel10_Status4,
      Red_Channel10_Status3,
      Green_Channel10_Status3,
      Blue_Channel10_Status3,
      Red_Channel10_Status2,
      Green_Channel10_Status2,
      Blue_Channel10_Status2,
      Red_Channel10_Status1,
      Green_Channel10_Status1,
      Blue_Channel10_Status1,
      Red_Channel2_Status5,
      Green_Channel2_Status5,
      Blue_Channel2_Status5,
      Red_Channel2_Status4,
      Green_Channel2_Status4,
      Blue_Channel2_Status4,
      Red_Channel2_Status3,
      Green_Channel2_Status3,
      Blue_Channel2_Status3,
      Red_Channel2_Status2,
      Green_Channel2_Status2,
      Blue_Channel2_Status2,
      Red_Channel2_Status1,
      Green_Channel2_Status1,
      Blue_Channel2_Status1,
      Red_Channel9_Status5,
      Green_Channel9_Status5,
      Blue_Channel9_Status5,
      Red_Channel9_Status4,
      Green_Channel9_Status4,
      Blue_Channel9_Status4,
      Red_Channel9_Status3,
      Green_Channel9_Status3,
      Blue_Channel9_Status3,
      Red_Channel9_Status2,
      Green_Channel9_Status2,
      Blue_Channel9_Status2,
      Red_Channel9_Status1,
      Green_Channel9_Status1,
      Blue_Channel9_Status1,
      Red_Channel1_Status5,
      Green_Channel1_Status5,
      Blue_Channel1_Status5,
      Red_Channel1_Status4,
      Green_Channel1_Status4,
      Blue_Channel1_Status4,
      Red_Channel1_Status3,
      Green_Channel1_Status3,
      Blue_Channel1_Status3,
      Red_Channel1_Status2,
      Green_Channel1_Status2,
      Blue_Channel1_Status2,
      Red_Channel1_Status1,
      Green_Channel1_Status1,
      Blue_Channel1_Status1,
      LIGHTS_LEN
   };

};

#endif // NOT TimeLordServerPanelH
