#ifndef BarCounterPanelH
#define BarCounterPanelH

#include "BarCounter.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemDisplayOLED.h>

struct BarCounter::Panel
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
      Text_Tempo = 0,
      // oled
      Pixels_Display = 1,
      DISPLAYS_LEN = 2
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Reset = 0,
      Clock = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // lcds
      RGB_Tempo = 0,
      LIGHTS_LEN = 3
   };

};

#endif // NOT BarCounterPanelH
