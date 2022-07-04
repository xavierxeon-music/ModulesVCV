#ifndef TimeLordPanelH
#define TimeLordPanelH

#include "TimeLord.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemLightMeter.h>
#include <SchweineSystemDisplayOLED.h>

struct TimeLord::Panel
{
   enum ParamId
   {
      // buttons
      Mode = 0,
      BankUp = 1,
      // switches
      // ledbuttons
      // knobs
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      Text_Channel8_Value = 0,
      Text_Channel7_Value = 1,
      Text_Channel6_Value = 2,
      Text_Channel5_Value = 3,
      Text_Channel4_Value = 4,
      Text_Channel3_Value = 5,
      Text_Channel2_Value = 6,
      Text_Channel1_Value = 7,
      // oled
      Pixels_Display = 8,
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
      Pass = 0,
      Reset = 1,
      Clock = 2,
      Channel8_Pass = 3,
      Channel7_Pass = 4,
      Channel6_Pass = 5,
      Channel5_Pass = 6,
      Channel4_Pass = 7,
      Channel3_Pass = 8,
      Channel2_Pass = 9,
      Channel1_Pass = 10,
      INPUTS_LEN = 11
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
      // ledbuttons
      // lcds
      RGB_Channel8_Value = 0,
      RGB_Channel7_Value = 3,
      RGB_Channel6_Value = 6,
      RGB_Channel5_Value = 9,
      RGB_Channel4_Value = 12,
      RGB_Channel3_Value = 15,
      RGB_Channel2_Value = 18,
      RGB_Channel1_Value = 21,
      LIGHTS_LEN = 24
   };

};

#endif // NOT TimeLordPanelH
