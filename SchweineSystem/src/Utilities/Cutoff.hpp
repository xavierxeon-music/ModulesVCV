#ifndef CutoffHPP
#define CutoffHPP

#include "Cutoff.h"

#include <SvinOrigin.h>

struct Cutoff::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      // sliders
      Over = 0,
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
      Input = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      Output = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      RGB_Over = 0,
      LIGHTS_LEN = 3
   };

};

void Cutoff::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Over, 0.0f, 1.0f, 0.0f, "Over");

   configInput(Panel::Input, "Input");

   configOutput(Panel::Output, "Output");
}

void CutoffWidget::setup()
{
   makePanel("res/Utilities/Cutoff.svg");

   makeSlider(this, Vec(22.50, 135.40), Cutoff::Panel::Over, Cutoff::Panel::RGB_Over);

   makeInput(this, Vec(22.50, 311.60),  Cutoff::Panel::Input, false);

   makeOutput(this, Vec(22.50, 355.83), Cutoff::Panel::Output, false);
}

#endif // NOT CutoffHPP
