#ifndef FlameCCPanelH
#define FlameCCPanelH

#include "FlameCC.h"

struct FlameCC::Panel
{
   enum ParamId
   {
      Connect,
      PARAMS_LEN
   };

   enum InputId
   {
      Row8_InB,
      Row8_InA,
      Row7_InB,
      Row7_InA,
      Row6_InB,
      Row6_InA,
      Row5_InB,
      Row5_InA,
      Row4_InB,
      Row4_InA,
      Row3_InB,
      Row3_InA,
      Row2_InB,
      Row2_InA,
      Row1_InB,
      Row1_InA,
      INPUTS_LEN
   };

   enum OutputId
   {
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_Connect,
      Green_Connect,
      Blue_Connect,
      LIGHTS_LEN
   };

};

#endif // NOT FlameCCPanelH
