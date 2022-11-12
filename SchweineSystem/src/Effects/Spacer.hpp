#ifndef SpacerHPP
#define SpacerHPP

#include "Spacer.h"

#include <SvinOrigin.h>

struct Spacer::Panel
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
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      In = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      RightOut = 0,
      LeftOut = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      LIGHTS_LEN = 0
   };

};

void Spacer::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::In, "In");

   configOutput(Panel::RightOut, "RightOut");
   configOutput(Panel::LeftOut, "LeftOut");
}

void SpacerWidget::setup()
{
   makePanel("res/Effects/Spacer.svg");

   makeInput(this, Vec(51.09, 285.55),  Spacer::Panel::In, false);

   makeOutput(this, Vec(51.09, 355.83), Spacer::Panel::RightOut, false);
   makeOutput(this, Vec(51.09, 323.07), Spacer::Panel::LeftOut, false);
}

#endif // NOT SpacerHPP
