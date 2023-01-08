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

   makeKnob(this, Vec(30.47, 205.79), Spacer::Panel::Delay, 3);
   makeKnob(this, Vec(30.24, 144.25), Spacer::Panel::Feedback, 3);
   makeKnob(this, Vec(30.24, 82.71), Spacer::Panel::Cutoff, 3);

   makeInput(this, Vec(30.16, 258.16),  Spacer::Panel::In, false);

   makeOutput(this, Vec(30.00, 355.83), Spacer::Panel::RightOut, false);
   makeOutput(this, Vec(30.00, 309.04), Spacer::Panel::LeftOut, false);
}

#endif // NOT SpacerHPP
