#ifndef BitBusBitOutPanelH
#define BitBusBitOutPanelH

#include "BitBusBitOut.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

struct BitBusBitOut::Panel
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
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      BitOut8 = 0,
      BitOut7 = 1,
      BitOut6 = 2,
      BitOut5 = 3,
      BitOut4 = 4,
      BitOut3 = 5,
      BitOut2 = 6,
      BitOut1 = 7,
      OUTPUTS_LEN = 8
   };

   enum LightId
   {
      // leds
      RGB_BusIn = 0,
      RGB_BusOut = 3,
      // ledbuttons
      // lcds
      LIGHTS_LEN = 6
   };

};

#endif // NOT BitBusBitOutPanelH
