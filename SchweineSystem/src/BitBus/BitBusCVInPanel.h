#ifndef BitBusCVInPanelH
#define BitBusCVInPanelH

#include "BitBusCVIn.h"

#include <SvinCommon.h>
#include <SvinLED.h>
#include <SvinInput.h>

struct BitBusCVIn::Panel
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
      CVIn = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_BusOut = 0,
      // ledbuttons
      // lcds
      LIGHTS_LEN = 3
   };

};

#endif // NOT BitBusCVInPanelH
