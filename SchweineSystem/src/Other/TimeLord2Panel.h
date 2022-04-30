#ifndef TimeLord2PanelH
#define TimeLord2PanelH

#include "TimeLord2.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLightMeter.h>
#include <SchweineSystemOLEDDisplay.h>

struct TimeLord2::Panel
{
   enum ParamId
   {
      // buttons
      Bank_Up = 0,
      Mode = 1,
      // ledbuttons
      // knobs
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      // oled
      Pixels_Display = 0,
      DISPLAYS_LEN = 1
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
      Reset = 0,
      Clock = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      Channel8_Output = 0,
      Channel7_Output = 1,
      Channel6_Output = 2,
      Channel5_Output = 3,
      Channel4_Output = 4,
      Channel3_Output = 5,
      Channel2_Output = 6,
      Channel1_Output = 7,
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

#endif // NOT TimeLord2PanelH
