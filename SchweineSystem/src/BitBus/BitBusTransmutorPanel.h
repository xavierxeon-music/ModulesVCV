#ifndef BitBusTransmutorPanelH
#define BitBusTransmutorPanelH

#include "BitBusTransmutor.h"

#include <SvinCommon.h>
#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinLED.h>
#include <SvinSlider.h>
#include <SvinInput.h>

struct BitBusTransmutor::Panel
{
   enum ParamId
   {
      // buttons
      Down = 0,
      Up = 1,
      // switches
      // ledbuttons
      // knobs
      // sliders
      Mix = 2,
      PARAMS_LEN = 3
   };

   enum DisplayId
   {
      // lcd
      Text_Bank = 0,
      // oled
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Scan = 0,
      INPUTS_LEN = 1
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
      RGB_Mix = 6,
      LIGHTS_LEN = 9
   };

};

#endif // NOT BitBusTransmutorPanelH
