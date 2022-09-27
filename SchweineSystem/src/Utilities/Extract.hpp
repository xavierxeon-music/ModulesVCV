#ifndef ExtractHPP
#define ExtractHPP

#include "Extract.h"

#include <SvinOrigin.h>

struct Extract::Panel
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
      AudioInput = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      AudioOutput = 0,
      Gate = 1,
      Pitch = 2,
      OUTPUTS_LEN = 3
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      LIGHTS_LEN = 0
   };

};

void Extract::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::AudioInput, "AudioInput");

   configOutput(Panel::AudioOutput, "AudioOutput");
   configOutput(Panel::Gate, "Gate");
   configOutput(Panel::Pitch, "Pitch");
}

void ExtractWidget::setup()
{
   makePanel("res/Utilities/Extract.svg");

   makeInput(this, Vec(30.00, 311.60),  Extract::Panel::AudioInput, false);

   makeOutput(this, Vec(30.00, 355.83), Extract::Panel::AudioOutput, false);
   makeOutput(this, Vec(30.24, 206.38), Extract::Panel::Gate, true);
   makeOutput(this, Vec(29.71, 159.32), Extract::Panel::Pitch, true);
}

#endif // NOT ExtractHPP
