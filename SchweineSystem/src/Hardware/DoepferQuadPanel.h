#ifndef DoepferQuadPanelH
#define DoepferQuadPanelH

#include "DoepferQuad.h"

#include <SchweineSystemCommon.h>

struct DoepferQuad::Panel
{
   enum ParamId
   {
      // buttons
      // ledbuttons
      Connect = 0,
      // knobs
      PARAMS_LEN = 1
   };

   enum DisplayId
   {
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Channel4_In3 = 0,
      Channel4_In2 = 1,
      Channel4_In1 = 2,
      Channel3_In3 = 3,
      Channel3_In2 = 4,
      Channel3_In1 = 5,
      Channel2_In3 = 6,
      Channel2_In2 = 7,
      Channel2_In1 = 8,
      Channel1_In3 = 9,
      Channel1_In2 = 10,
      Channel1_In1 = 11,
      INPUTS_LEN = 12
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // buttons
      RGB_Connect = 0,
      // displays
      LIGHTS_LEN = 3
   };

};

#endif // NOT DoepferQuadPanelH
