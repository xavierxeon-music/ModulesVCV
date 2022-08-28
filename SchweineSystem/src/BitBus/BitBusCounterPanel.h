#ifndef BitBusCounterPanelH
#define BitBusCounterPanelH

#include "BitBusCounter.h"

#include <SvinCommon.h>
#include <SvinDisplayLCD.h>
#include <SvinLED.h>
#include <SvinInput.h>

struct BitBusCounter::Panel
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
      Text_Number = 0,
      // oled
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Reset = 0,
      Down = 1,
      Up = 2,
      INPUTS_LEN = 3
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_Bit8_Indicator = 0,
      RGB_Bit7_Indicator = 3,
      RGB_Bit6_Indicator = 6,
      RGB_Bit5_Indicator = 9,
      RGB_Bit4_Indicator = 12,
      RGB_Bit3_Indicator = 15,
      RGB_Bit2_Indicator = 18,
      RGB_Bit1_Indicator = 21,
      RGB_BusOut = 24,
      // ledbuttons
      // lcds
      RGB_Number = 27,
      LIGHTS_LEN = 30
   };

};

#endif // NOT BitBusCounterPanelH
