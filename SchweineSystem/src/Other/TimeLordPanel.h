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
      BankUp = 0,
      Mode = 1,
      // switches
      // ledbuttons
      // knobs
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      Text_Bank = 0,
      Text_Channel8_Value = 1,
      Text_Channel7_Value = 2,
      Text_Channel6_Value = 3,
      Text_Channel5_Value = 4,
      Text_Channel4_Value = 5,
      Text_Channel3_Value = 6,
      Text_Channel2_Value = 7,
      Text_Channel1_Value = 8,
      // oled
      Pixels_Display = 9,
      DISPLAYS_LEN = 10
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
      Upload = 0,
      Pass = 1,
      Reset = 2,
      Clock = 3,
      Channel8_Pass = 4,
      Channel7_Pass = 5,
      Channel6_Pass = 6,
      Channel5_Pass = 7,
      Channel4_Pass = 8,
      Channel3_Pass = 9,
      Channel2_Pass = 10,
      Channel1_Pass = 11,
      INPUTS_LEN = 12
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
      RGB_Bank = 0,
      RGB_Channel8_Value = 3,
      RGB_Channel7_Value = 6,
      RGB_Channel6_Value = 9,
      RGB_Channel5_Value = 12,
      RGB_Channel4_Value = 15,
      RGB_Channel3_Value = 18,
      RGB_Channel2_Value = 21,
      RGB_Channel1_Value = 24,
      LIGHTS_LEN = 27
   };

};

#endif // NOT TimeLordPanelH
