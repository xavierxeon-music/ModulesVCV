#ifndef BitBusCVOutPanelH
#define BitBusCVOutPanelH

#include "BitBusCVOut.h"

#include <SvinCommon.h>
#include <SvinLED.h>
#include <SvinOutput.h>

struct BitBusCVOut::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      // sliders
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
      CVOut = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      RGB_BusIn = 0,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 3
   };

};

#endif // NOT BitBusCVOutPanelH
