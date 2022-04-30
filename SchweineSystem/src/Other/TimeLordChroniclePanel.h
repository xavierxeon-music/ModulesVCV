#ifndef TimeLordChroniclePanelH
#define TimeLordChroniclePanelH

#include "TimeLordChronicle.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>
#include <SchweineSystemLightMeter.h>

struct TimeLordChronicle::Panel
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
      // lcd
      Text_Channel8_Display = 0,
      Text_Channel7_Display = 1,
      Text_Channel6_Display = 2,
      Text_Channel5_Display = 3,
      Text_Channel4_Display = 4,
      Text_Channel3_Display = 5,
      Text_Channel2_Display = 6,
      Text_Channel1_Display = 7,
      // oled
      DISPLAYS_LEN = 8
   };

   enum MeterId
   {
      Value_Channel8_Strip = 0,
      Value_Channel7_Strip = 1,
      Value_Channel6_Strip = 2,
      Value_Channel5_Strip = 3,
      Value_Channel4_Strip = 4,
      Value_Channel3_Strip = 5,
      Value_Channel2_Strip = 6,
      Value_Channel1_Strip = 7,
      METERS_LEN = 8
   };

   enum InputId
   {
      Channel8_Input = 0,
      Channel7_Input = 1,
      Channel6_Input = 2,
      Channel5_Input = 3,
      Channel4_Input = 4,
      Channel3_Input = 5,
      Channel2_Input = 6,
      Channel1_Input = 7,
      INPUTS_LEN = 8
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // buttons
      // displays
      RGB_Channel8_Display = 0,
      RGB_Channel7_Display = 3,
      RGB_Channel6_Display = 6,
      RGB_Channel5_Display = 9,
      RGB_Channel4_Display = 12,
      RGB_Channel3_Display = 15,
      RGB_Channel2_Display = 18,
      RGB_Channel1_Display = 21,
      LIGHTS_LEN = 24
   };

};

#endif // NOT TimeLordChroniclePanelH
