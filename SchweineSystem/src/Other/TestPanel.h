#ifndef TestPanelH
#define TestPanelH

#include "Test.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>
#include <SchweineSystemLight.h>
#include <SchweineSystemMeter.h>

struct Test::Panel
{
   enum ParamId
   {
      Channel1_Up,
      Value_Channel1_Display,
      Value_Channel1_Strip,
      PARAMS_LEN
   };

   enum InputId
   {
      Channel1_Input,
      INPUTS_LEN
   };

   enum OutputId
   {
      Channel1_Output,
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_Channel1_Division,
      Green_Channel1_Division,
      Blue_Channel1_Division,
      Red_Channel1_Up,
      Green_Channel1_Up,
      Blue_Channel1_Up,
      Red_Channel1_Display,
      Green_Channel1_Display,
      Blue_Channel1_Display,
      LIGHTS_LEN
   };

   Panel();
};

#endif // NOT TestPanelH
