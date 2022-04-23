#ifndef DoepferQuadPanelH
#define DoepferQuadPanelH

#include "DoepferQuad.h"

#include <SchweineSystemCommon.h>

struct DoepferQuad::Panel
{
   enum ParamId
   {
      Connect,
      PARAMS_LEN
   };

   enum InputId
   {
      Channel4_In3,
      Channel4_In2,
      Channel4_In1,
      Channel3_In3,
      Channel3_In2,
      Channel3_In1,
      Channel2_In3,
      Channel2_In2,
      Channel2_In1,
      Channel1_In3,
      Channel1_In2,
      Channel1_In1,
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

   Panel();
};

#endif // NOT DoepferQuadPanelH
