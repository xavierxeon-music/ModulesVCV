#ifndef GateLatchPanelH
#define GateLatchPanelH

#include "GateLatch.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

struct GateLatch::Panel
{
   enum ParamId
   {
      // buttons
      Reset_Button = 0,
      // ledbuttons
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
      METERS_LEN = 0
   };

   enum InputId
   {
      Reset_Input = 0,
      Row8_In = 1,
      Row7_In = 2,
      Row6_In = 3,
      Row5_In = 4,
      Row4_In = 5,
      Row3_In = 6,
      Row2_In = 7,
      Row1_In = 8,
      INPUTS_LEN = 9
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
      RGB_Row8_Status1 = 0,
      RGB_Row7_Status1 = 3,
      RGB_Row6_Status1 = 6,
      RGB_Row5_Status1 = 9,
      RGB_Row4_Status1 = 12,
      RGB_Row3_Status1 = 15,
      RGB_Row2_Status1 = 18,
      RGB_Row1_Status1 = 21,
      // buttons
      // displays
      LIGHTS_LEN = 24
   };

};

#endif // NOT GateLatchPanelH
