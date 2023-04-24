#ifndef MetroControlHPP
#define MetroControlHPP

#include "MetroControl.h"

#include <SvinOrigin.h>

struct MetroControl::Panel
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

void MetroControl::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

void MetroControlWidget::setup()
{
   makePanel("res/Utilities/MetroControl.svg");

   makeLED(this, Vec(30.00, 360.06), MetroControl::Panel::RGB_Connected);

   makeOLED(this, Vec(19.00, 219.17), MetroControl::Panel::Pixels_Reset, 20, 20);
   makeOLED(this, Vec(19.00, 190.00), MetroControl::Panel::Pixels_PlayPause, 20, 20);
}

#endif // NOT MetroControlHPP
