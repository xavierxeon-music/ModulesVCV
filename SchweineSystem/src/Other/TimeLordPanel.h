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
      Mode,
      Bank_Up,
      Value_Bank_Display,
      Value_Channel8_Display,
      Value_Channel7_Display,
      Value_Channel6_Display,
      Value_Channel5_Display,
      Value_Channel4_Display,
      Value_Channel3_Display,
      Value_Channel2_Display,
      Value_Channel1_Display,
      Value_Channel8_Strip,
      Value_Channel7_Strip,
      Value_Channel6_Strip,
      Value_Channel5_Strip,
      Value_Channel4_Strip,
      Value_Channel3_Strip,
      Value_Channel2_Strip,
      Value_Channel1_Strip,
      PARAMS_LEN
   };

   enum InputId
   {
      Reset,
      Clock,
      INPUTS_LEN
   };

   enum OutputId
   {
      Channel8_Output,
      Channel7_Output,
      Channel6_Output,
      Channel5_Output,
      Channel4_Output,
      Channel3_Output,
      Channel2_Output,
      Channel1_Output,
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_Current,
      Green_Current,
      Blue_Current,
      Red_Count,
      Green_Count,
      Blue_Count,
      Red_Length,
      Green_Length,
      Blue_Length,
      Red_Division,
      Green_Division,
      Blue_Division,
      Red_Mode,
      Green_Mode,
      Blue_Mode,
      Red_Bank_Up,
      Green_Bank_Up,
      Blue_Bank_Up,
      Red_Bank_Display,
      Green_Bank_Display,
      Blue_Bank_Display,
      Red_Channel8_Display,
      Green_Channel8_Display,
      Blue_Channel8_Display,
      Red_Channel7_Display,
      Green_Channel7_Display,
      Blue_Channel7_Display,
      Red_Channel6_Display,
      Green_Channel6_Display,
      Blue_Channel6_Display,
      Red_Channel5_Display,
      Green_Channel5_Display,
      Blue_Channel5_Display,
      Red_Channel4_Display,
      Green_Channel4_Display,
      Blue_Channel4_Display,
      Red_Channel3_Display,
      Green_Channel3_Display,
      Blue_Channel3_Display,
      Red_Channel2_Display,
      Green_Channel2_Display,
      Blue_Channel2_Display,
      Red_Channel1_Display,
      Green_Channel1_Display,
      Blue_Channel1_Display,
      LIGHTS_LEN
   };

   Panel();
};

#endif // NOT TimeLordPanelH
