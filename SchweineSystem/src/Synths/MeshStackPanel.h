#ifndef MeshStackPanelH
#define MeshStackPanelH

#include "MeshStack.h"

#include <SvinCommon.h>
#include <SvinKnob.h>
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
      Two = 1,
      One = 2,
      PARAMS_LEN = 3
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
      // ledbuttons
      // sliders
      RGB_Two = 0,
      RGB_One = 3,
      LIGHTS_LEN = 6
   };

};

#endif // NOT MeshStackPanelH
