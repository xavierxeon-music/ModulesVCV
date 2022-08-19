#ifndef PamelasClockPanelH
#define PamelasClockPanelH

#include "PamelasClock.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemButtonLED.h>

struct PamelasClock::Panel
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
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      Reset = 0,
      Clock = 1,
      OUTPUTS_LEN = 2
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

#endif // NOT PamelasClockPanelH
