#ifndef MeshStackPanelH
#define MeshStackPanelH

#include "MeshStack.h"

#include <SvinCommon.h>
#include <SvinKnob.h>
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
      Knob_Mode = 0,
      PARAMS_LEN = 1
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
      // lcds
      LIGHTS_LEN = 0
   };

};

#endif // NOT MeshStackPanelH
