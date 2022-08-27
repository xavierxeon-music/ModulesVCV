#ifndef FlameCCSenderPanelH
#define FlameCCSenderPanelH

#include "FlameCCSender.h"

#include <SvinCommon.h>
#include <SvinButtonLED.h>
#include <SvinSwitch.h>
#include <SvinInput.h>

struct FlameCCSender::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      Half = 0,
      // ledbuttons
      Connect = 1,
      // knobs
      PARAMS_LEN = 2
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
      Voltages = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
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

#endif // NOT FlameCCSenderPanelH
