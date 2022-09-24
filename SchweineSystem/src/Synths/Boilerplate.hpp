#ifndef BoilerplateHPP
#define BoilerplateHPP

#include "Boilerplate.h"

#include <SvinOrigin.h>

struct Boilerplate::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      StallZero = 0,
      // knobs
      Offset = 1,
      FMAttenuate = 2,
      // sliders
      Shape = 3,
      PARAMS_LEN = 4
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
      Pitch = 0,
      Sync = 1,
      FM = 2,
      INPUTS_LEN = 3
   };

   enum OutputId
   {
      Out = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_StallZero = 0,
      // sliders
      RGB_Shape = 3,
      LIGHTS_LEN = 6
   };

};

void Boilerplate::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Shape, 0.0f, 1.0f, 0.0f, "Shape");

   configButton(Panel::StallZero, "StallZero");

   configParam(Panel::Offset, -1.f, 1.f, 0.f, "Offset");
   configParam(Panel::FMAttenuate, -1.f, 1.f, 0.f, "FMAttenuate");

   configInput(Panel::Pitch, "Pitch");
   configInput(Panel::Sync, "Sync");
   configInput(Panel::FM, "FM");

   configOutput(Panel::Out, "Out");
}

void BoilerplateWidget::setup()
{
   makePanel("res/Synths/Boilerplate.svg");

   makeSlider(this, Vec(65.93, 107.15), Boilerplate::Panel::Shape, Boilerplate::Panel::RGB_Shape);

   makeLEDButton(this, Vec(23.99, 356.10), Boilerplate::Panel::StallZero, Boilerplate::Panel::RGB_StallZero);

   makeKnob(this, Vec(45.20, 284.73), Boilerplate::Panel::Offset, 4);
   makeKnob(this, Vec(65.93, 183.13), Boilerplate::Panel::FMAttenuate, 2);

   makeInput(this, Vec(24.17, 233.05),  Boilerplate::Panel::Pitch, true);
   makeInput(this, Vec(64.55, 233.42),  Boilerplate::Panel::Sync, false);
   makeInput(this, Vec(24.17, 183.13),  Boilerplate::Panel::FM, false);

   makeOutput(this, Vec(65.83, 355.83), Boilerplate::Panel::Out, false);
}

#endif // NOT BoilerplateHPP
