#ifndef TimeLordPanelH
#define TimeLordPanelH

#include "TimeLord.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemLightMeter.h>
#include <SchweineSystemDisplayOLED.h>

struct TimeLord::Panel
{
   enum ParamId
   {
      // buttons
      ModeManual = 0,
      Display = 1,
      BankUp = 2,
      // switches
      // ledbuttons
      Silence = 3,
      // knobs
      PARAMS_LEN = 4
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
      ModeCV = 1,
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
      RGB_Internal_Status = 0,
      RGB_Remote_Status = 3,
      RGB_Input_Status = 6,
      // ledbuttons
      RGB_Silence = 9,
      // lcds
      RGB_Bank = 12,
      RGB_Channel8_Value = 15,
      RGB_Channel7_Value = 18,
      RGB_Channel6_Value = 21,
      RGB_Channel5_Value = 24,
      RGB_Channel4_Value = 27,
      RGB_Channel3_Value = 30,
      RGB_Channel2_Value = 33,
      RGB_Channel1_Value = 36,
      LIGHTS_LEN = 39
   };

};

#endif // NOT TimeLordPanelH
