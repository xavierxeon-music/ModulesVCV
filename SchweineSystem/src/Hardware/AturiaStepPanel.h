#ifndef AturiaStepPanelH
#define AturiaStepPanelH

#include "AturiaStep.h"

#include <SyCommon.h>
#include <SyButton.h>
#include <SyDisplayLCD.h>
#include <SyButtonLED.h>

struct AturiaStep::Panel
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
      // switches
      // ledbuttons
      Connect = 8,
      Drums = 9,
      // knobs
      PARAMS_LEN = 10
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
      // ledbuttons
      RGB_Connect = 0,
      RGB_Drums = 3,
      // lcds
      RGB_Channel4_Pattern = 6,
      RGB_Channel3_Pattern = 9,
      RGB_Channel2_Pattern = 12,
      RGB_Channel1_Pattern = 15,
      LIGHTS_LEN = 18
   };

};

#endif // NOT AturiaStepPanelH
