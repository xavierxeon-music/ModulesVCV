#ifndef TestPanelH
#define TestPanelH

#include "Test.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>
#include <SchweineSystemLight.h>
#include <SchweineSystemLightMeter.h>

struct Test::Panel
{
   enum ParamId
   {
      // buttons
      Channel1_Up = 0,
      // knobs
      PARAMS_LEN = 1
   };

   enum DisplayId
   {
      Text_Channel1_Display = 0,
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      Value_Channel1_Strip = 0,
      METERS_LEN = 1
   };

   enum InputId
   {
      Channel1_Input = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      Channel1_Output = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      RGB_Channel1_Division = 0,
      // buttons
      RGB_Channel1_Up = 3,
      // displays
      RGB_Channel1_Display = 6,
      LIGHTS_LEN = 9
   };

};

#endif // NOT TestPanelH
