#ifndef LinkControlHPP
#define LinkControlHPP

#include "LinkControl.h"

#include <SvinOrigin.h>

struct LinkControl::Panel
{
   enum ParamId
   {
      // buttons
      One_Down = 0,
      One_Up = 1,
      Ten_Down = 2,
      Ten_Up = 3,
      Hundred_Down = 4,
      Hundred_Up = 5,
      // switches
      // ledbuttons
      Active = 6,
      // knobs
      // sliders
      PARAMS_LEN = 7
   };

   enum DisplayId
   {
      // lcd
      Text_Tempo = 0,
      // oled
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      Value_Sync = 0,
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

   configButton(Panel::One_Down, "One_Down");
   configButton(Panel::One_Up, "One_Up");
   configButton(Panel::Ten_Down, "Ten_Down");
   configButton(Panel::Ten_Up, "Ten_Up");
   configButton(Panel::Hundred_Down, "Hundred_Down");
   configButton(Panel::Hundred_Up, "Hundred_Up");

   configButton(Panel::Active, "Active");
}

void LinkControlWidget::setup()
{
   makePanel("res/Utilities/LinkControl.svg");

   makeButton(this, Vec(56.34, 183.98), LinkControl::Panel::One_Down);
   makeButton(this, Vec(56.34, 167.16), LinkControl::Panel::One_Up);
   makeButton(this, Vec(37.50, 183.98), LinkControl::Panel::Ten_Down);
   makeButton(this, Vec(37.50, 167.16), LinkControl::Panel::Ten_Up);
   makeButton(this, Vec(18.66, 183.98), LinkControl::Panel::Hundred_Down);
   makeButton(this, Vec(18.66, 167.16), LinkControl::Panel::Hundred_Up);

   makeLEDButton(this, Vec(37.50, 283.88), LinkControl::Panel::Active, LinkControl::Panel::RGB_Active);

   makeLCD(this, Vec(12.50, 128.21), 3, LinkControl::Panel::Text_Tempo, 18);

   makeMeter(this, Vec(33.32, 305.07), 10, LinkControl::Panel::Value_Sync);
}

#endif // NOT LinkControlHPP
