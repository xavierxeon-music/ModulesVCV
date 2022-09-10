#ifndef BitBusTransmutorPanelH
#define BitBusTransmutorPanelH

#include "BitBusTransmutor.h"

#include <SvinCommon.h>
#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinLED.h>

struct BitBusTransmutor::Panel
{
   enum ParamId
   {
      // buttons
      Seed_Up = 0,
      Seed_Down = 1,
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      Text_Seed_Number = 0,
      // oled
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
      // sliders
      LIGHTS_LEN = 6
   };

};

#endif // NOT BitBusTransmutorPanelH
