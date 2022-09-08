#ifndef MeshStackPanelH
#define MeshStackPanelH

#include "MeshStack.h"

#include <SvinCommon.h>
#include <SvinKnob.h>
#include <SvinLED.h>
#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct MeshStack::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      Mode = 0,
      // sliders
      Blue = 1,
      Green = 2,
      Red = 3,
      PARAMS_LEN = 4
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
      Pitch = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      Out = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      RGB_Color = 0,
      // ledbuttons
      // sliders
      RGB_Blue = 3,
      RGB_Green = 6,
      RGB_Red = 9,
      LIGHTS_LEN = 12
   };

};

#endif // NOT MeshStackPanelH
