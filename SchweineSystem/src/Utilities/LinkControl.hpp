#ifndef LinkControlHPP
#define LinkControlHPP

#include "LinkControl.h"

#include <SvinOrigin.h>

struct LinkControl::Panel
{
   enum ParamId
   {
      // buttons
      Down = 0,
      Up = 1,
      // switches
      // ledbuttons
      Active = 2,
      // knobs
      // sliders
      PARAMS_LEN = 3
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
      // ledbuttons
      RGB_Active = 0,
      // sliders
      LIGHTS_LEN = 3
   };

};

void LinkControl::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Down, "Down");
   configButton(Panel::Up, "Up");

   configButton(Panel::Active, "Active");
}

void LinkControlWidget::setup()
{
   makePanel("res/Utilities/LinkControl.svg");

   makeButton(this, Vec(36.71, 270.45), LinkControl::Panel::Down);
   makeButton(this, Vec(36.71, 253.63), LinkControl::Panel::Up);

   makeLEDButton(this, Vec(37.50, 202.33), LinkControl::Panel::Active, LinkControl::Panel::RGB_Active);

   makeOLED(this, Vec(10.00, 95.00), LinkControl::Panel::Pixels_Display, 53, 60);
}

#endif // NOT LinkControlHPP
