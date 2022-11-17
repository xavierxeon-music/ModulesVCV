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
      Delay = 0,
      Feedback = 1,
      Cutoff = 2,
      // sliders
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

   configParam(Panel::Delay, -1.f, 1.f, 0.f, "Delay");
   configParam(Panel::Feedback, -1.f, 1.f, 0.f, "Feedback");
   configParam(Panel::Cutoff, -1.f, 1.f, 0.f, "Cutoff");

   configInput(Panel::In, "In");

   configOutput(Panel::RightOut, "RightOut");
   configOutput(Panel::LeftOut, "LeftOut");
}

void SpacerWidget::setup()
{
   makePanel("res/Effects/Spacer.svg");

   makeKnob(this, Vec(45.24, 213.16), Spacer::Panel::Delay, 3);
   makeKnob(this, Vec(45.00, 143.62), Spacer::Panel::Feedback, 3);
   makeKnob(this, Vec(45.00, 74.09), Spacer::Panel::Cutoff, 3);

   makeInput(this, Vec(51.09, 285.55),  Spacer::Panel::In, false);

   makeOutput(this, Vec(51.09, 355.83), Spacer::Panel::RightOut, false);
   makeOutput(this, Vec(51.09, 323.07), Spacer::Panel::LeftOut, false);
}

#endif // NOT SpacerHPP
