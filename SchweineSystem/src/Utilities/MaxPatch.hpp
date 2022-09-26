#ifndef MaxPatchHPP
#define MaxPatchHPP

#include "MaxPatch.h"

#include <SvinOrigin.h>

struct MaxPatch::Panel
{
   enum ParamId
   {
      // buttons
      Kill = 0,
      Restart = 1,
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 2
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
      RGB_Connected = 0,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 3
   };

};

void MaxPatch::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Kill, "Kill");
   configButton(Panel::Restart, "Restart");
}

void MaxPatchWidget::setup()
{
   makePanel("res/Utilities/MaxPatch.svg");

   makeButton(this, Vec(29.50, 290.25), MaxPatch::Panel::Kill);
   makeButton(this, Vec(30.00, 233.36), MaxPatch::Panel::Restart);

   makeLED(this, Vec(30.00, 352.32), MaxPatch::Panel::RGB_Connected);

   makeOLED(this, Vec(9.00, 125.34), MaxPatch::Panel::Pixels_Display, 40, 60);
}

#endif // NOT MaxPatchHPP
