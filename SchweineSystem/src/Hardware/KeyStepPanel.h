#ifndef KeyStepPanelH
#define KeyStepPanelH

#include "KeyStep.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>

struct KeyStep::Panel
{
   enum ParamId
   {
      // buttons
      Channel4_Up = 0,
      Channel4_Down = 1,
      Channel3_Up = 2,
      Channel3_Down = 3,
      Channel2_Up = 4,
      Channel2_Down = 5,
      Channel1_Up = 6,
      Channel1_Down = 7,
      // ledbuttons
      Connect = 8,
      // knobs
      PARAMS_LEN = 9
   };

   enum DisplayId
   {
      // lcd
      Text_Channel4_Pattern = 0,
      Text_Channel3_Pattern = 1,
      Text_Channel2_Pattern = 2,
      Text_Channel1_Pattern = 3,
      // oled
      DISPLAYS_LEN = 4
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Channel4_Select = 0,
      Channel3_Select = 1,
      Channel2_Select = 2,
      Channel1_Select = 3,
      INPUTS_LEN = 4
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // buttons
      RGB_Connect = 0,
      // displays
      RGB_Channel4_Pattern = 3,
      RGB_Channel3_Pattern = 6,
      RGB_Channel2_Pattern = 9,
      RGB_Channel1_Pattern = 12,
      LIGHTS_LEN = 15
   };

};

#endif // NOT KeyStepPanelH
