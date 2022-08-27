#ifndef TimeLordCompanionPanelH
#define TimeLordCompanionPanelH

#include "TimeLordCompanion.h"

#include <SvinButtonLED.h>
#include <SvinCommon.h>
#include <SvinSwitch.h>

struct TimeLordCompanion::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      Channel8_Silence = 0,
      Channel7_Silence = 1,
      Channel6_Silence = 2,
      Channel5_Silence = 3,
      Channel4_Silence = 4,
      Channel3_Silence = 5,
      Channel2_Silence = 6,
      Channel1_Silence = 7,
      // ledbuttons
      Channel8_Steady = 8,
      Channel7_Steady = 9,
      Channel6_Steady = 10,
      Channel5_Steady = 11,
      Channel4_Steady = 12,
      Channel3_Steady = 13,
      Channel2_Steady = 14,
      Channel1_Steady = 15,
      // knobs
      PARAMS_LEN = 16
   };

   enum DisplayId
   {
      // lcd
      // oled
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Channel8_SteadyOverride = 0,
      Channel7_SteadyOverride = 1,
      Channel6_SteadyOverride = 2,
      Channel5_SteadyOverride = 3,
      Channel4_SteadyOverride = 4,
      Channel3_SteadyOverride = 5,
      Channel2_SteadyOverride = 6,
      Channel1_SteadyOverride = 7,
      INPUTS_LEN = 8
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Channel8_Steady = 0,
      RGB_Channel7_Steady = 3,
      RGB_Channel6_Steady = 6,
      RGB_Channel5_Steady = 9,
      RGB_Channel4_Steady = 12,
      RGB_Channel3_Steady = 15,
      RGB_Channel2_Steady = 18,
      RGB_Channel1_Steady = 21,
      // lcds
      LIGHTS_LEN = 24
   };
};

#endif // NOT TimeLordCompanionPanelH
