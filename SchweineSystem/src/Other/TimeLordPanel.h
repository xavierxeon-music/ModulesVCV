#ifndef TimeLordPanelH
#define TimeLordPanelH

#include "TimeLord.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>
#include <SchweineSystemLight.h>
#include <SchweineSystemLightMeter.h>

struct TimeLord::Panel
{
   enum ParamId
   {
      // buttons
      Mode = 0,
      Bank_Up = 1,
      // knobs
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      Text_Bank_Display = 0,
      Text_Channel8_Display = 1,
      Text_Channel7_Display = 2,
      Text_Channel6_Display = 3,
      Text_Channel5_Display = 4,
      Text_Channel4_Display = 5,
      Text_Channel3_Display = 6,
      Text_Channel2_Display = 7,
      Text_Channel1_Display = 8,
      DISPLAYS_LEN = 9
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
      RGB_Current = 0,
      RGB_Count = 3,
      RGB_Length = 6,
      RGB_Division = 9,
      // buttons
      RGB_Mode = 12,
      RGB_Bank_Up = 15,
      // displays
      RGB_Bank_Display = 18,
      RGB_Channel8_Display = 21,
      RGB_Channel7_Display = 24,
      RGB_Channel6_Display = 27,
      RGB_Channel5_Display = 30,
      RGB_Channel4_Display = 33,
      RGB_Channel3_Display = 36,
      RGB_Channel2_Display = 39,
      RGB_Channel1_Display = 42,
      LIGHTS_LEN = 45
   };

};

#endif // NOT TimeLordPanelH
