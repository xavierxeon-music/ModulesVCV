#ifndef LinkControlHPP
#define LinkControlHPP

#include "LinkControl.h"

#include <SvinOrigin.h>

struct LinkControl::Panel
{
   enum ParamId
   {
      // buttons
      Hundred_Down = 0,
      Hundred_Up = 1,
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
      Text_Number = 0,
      // oled
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      Value_Channel1 = 0,
      METERS_LEN = 1
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

   configButton(Panel::Hundred_Down, "Hundred_Down");
   configButton(Panel::Hundred_Up, "Hundred_Up");

   configButton(Panel::Active, "Active");
}

void LinkControlWidget::setup()
{
   makePanel("res/Utilities/LinkControl.svg");

   makeButton(this, Vec(21.98, 183.98), LinkControl::Panel::Hundred_Down);
   makeButton(this, Vec(21.98, 167.16), LinkControl::Panel::Hundred_Up);

   makeLEDButton(this, Vec(37.50, 283.88), LinkControl::Panel::Active, LinkControl::Panel::RGB_Active);

   makeLCD(this, Vec(12.50, 128.21), 3, LinkControl::Panel::Text_Number, 18);

   makeMeter(this, Vec(33.32, 305.07), 5, LinkControl::Panel::Value_Channel1);
}

#endif // NOT LinkControlHPP
