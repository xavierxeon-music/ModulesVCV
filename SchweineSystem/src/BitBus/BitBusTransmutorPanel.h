#ifndef BitBusTransmutorPanelH
#define BitBusTransmutorPanelH

#include "BitBusTransmutor.h"

#include <SvinButton.h>
#include <SvinCommon.h>
#include <SvinDisplayOLED.h>
#include <SvinLED.h>

struct BitBusTransmutor::Panel
{
   enum ParamId
   {
      // buttons
      Display = 0,
      // switches
      // ledbuttons
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
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
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

#endif // NOT BitBusTransmutorPanelH
