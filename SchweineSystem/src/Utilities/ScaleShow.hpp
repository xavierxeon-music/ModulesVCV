#ifndef ScaleShowHPP
#define ScaleShowHPP

#include "ScaleShow.h"

#include <SvinOrigin.h>

struct ScaleShow::Panel
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
      Pixels_Reset = 0,
      Pixels_PlayPause = 1,
      DISPLAYS_LEN = 2
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

void ScaleShow::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

void ScaleShowWidget::setup()
{
   makePanel("res/Utilities/ScaleShow.svg");

   makeLED(this, Vec(30.00, 360.06), ScaleShow::Panel::RGB_Connected);

   makeOLED(this, Vec(19.00, 219.17), ScaleShow::Panel::Pixels_Reset, 20, 20);
   makeOLED(this, Vec(19.00, 190.00), ScaleShow::Panel::Pixels_PlayPause, 20, 20);
}

#endif // NOT ScaleShowHPP
