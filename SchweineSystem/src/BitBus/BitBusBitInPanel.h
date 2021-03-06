#ifndef BitBusBitInPanelH
#define BitBusBitInPanelH

#include "BitBusBitIn.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

struct BitBusBitIn::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      PARAMS_LEN = 0
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
      BitIn8 = 0,
      BitIn7 = 1,
      BitIn6 = 2,
      BitIn5 = 3,
      BitIn4 = 4,
      BitIn3 = 5,
      BitIn2 = 6,
      BitIn1 = 7,
      INPUTS_LEN = 8
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_BusOut = 0,
      RGB_BusIn = 3,
      // ledbuttons
      // lcds
      LIGHTS_LEN = 6
   };

};

#endif // NOT BitBusBitInPanelH
