#ifndef MetropolixClockPanelH
#define MetropolixClockPanelH

#include "MetropolixClock.h"

#include <SvinCommon.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct MetropolixClock::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Connect = 0,
      // knobs
      PARAMS_LEN = 1
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
      METERS_LEN = 0
   };

   enum InputId
   {
      Override_Reset = 0,
      Override_Clock = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      Reset = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Connect = 0,
      // lcds
      LIGHTS_LEN = 3
   };

};

#endif // NOT MetropolixClockPanelH
