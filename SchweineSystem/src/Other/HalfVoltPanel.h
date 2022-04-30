#ifndef HalfVoltPanelH
#define HalfVoltPanelH

#include "HalfVolt.h"

#include <SchweineSystemCommon.h>

struct HalfVolt::Panel
{
   enum ParamId
   {
      // buttons
      // ledbuttons
      // knobs
      PARAMS_LEN = 0
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
      Row8_In = 0,
      Row7_In = 1,
      Row6_In = 2,
      Row5_In = 3,
      Row4_In = 4,
      Row3_In = 5,
      Row2_In = 6,
      Row1_In = 7,
      INPUTS_LEN = 8
   };

   enum OutputId
   {
      Row8_Out = 0,
      Row7_Out = 1,
      Row6_Out = 2,
      Row5_Out = 3,
      Row4_Out = 4,
      Row3_Out = 5,
      Row2_Out = 6,
      Row1_Out = 7,
      OUTPUTS_LEN = 8
   };

   enum LightId
   {
      // leds
      // buttons
      // displays
      LIGHTS_LEN = 0
   };

};

#endif // NOT HalfVoltPanelH
