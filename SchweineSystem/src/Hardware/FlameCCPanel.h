#ifndef FlameCCPanelH
#define FlameCCPanelH

#include "FlameCC.h"

#include <SchweineSystemCommon.h>

struct FlameCC::Panel
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
      Row8_InB = 0,
      Row8_InA = 1,
      Row7_InB = 2,
      Row7_InA = 3,
      Row6_InB = 4,
      Row6_InA = 5,
      Row5_InB = 6,
      Row5_InA = 7,
      Row4_InB = 8,
      Row4_InA = 9,
      Row3_InB = 10,
      Row3_InA = 11,
      Row2_InB = 12,
      Row2_InA = 13,
      Row1_InB = 14,
      Row1_InA = 15,
      INPUTS_LEN = 16
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

#endif // NOT FlameCCPanelH
