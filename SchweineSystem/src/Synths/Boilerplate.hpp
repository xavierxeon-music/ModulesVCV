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
      Poly = 0,
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
      Gate = 0,
      Pitch = 1,
      Sync = 2,
      FM = 3,
      INPUTS_LEN = 4
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
      RGB_Poly = 0,
      // sliders
      RGB_Shape = 3,
      LIGHTS_LEN = 6
   };

};

void Boilerplate::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Shape, 0.0f, 1.0f, 0.0f, "Shape");

   configButton(Panel::Poly, "Poly");

   configParam(Panel::Offset, -1.f, 1.f, 0.f, "Offset");
   configParam(Panel::FMAttenuate, -1.f, 1.f, 0.f, "FMAttenuate");

   configInput(Panel::Gate, "Gate");
   configInput(Panel::Pitch, "Pitch");
   configInput(Panel::Sync, "Sync");
   configInput(Panel::FM, "FM");

   configOutput(Panel::Out, "Out");
}

void BoilerplateWidget::setup()
{
   makePanel("res/Synths/Boilerplate.svg");

   makeSlider(this, Vec(65.93, 107.15), Boilerplate::Panel::Shape, Boilerplate::Panel::RGB_Shape);

   makeLEDButton(this, Vec(64.56, 206.57), Boilerplate::Panel::Poly, Boilerplate::Panel::RGB_Poly);

   makeKnob(this, Vec(45.20, 297.73), Boilerplate::Panel::Offset, 4);
   makeKnob(this, Vec(24.68, 206.57), Boilerplate::Panel::FMAttenuate, 2);

   makeInput(this, Vec(24.17, 355.83),  Boilerplate::Panel::Gate, true);
   makeInput(this, Vec(24.17, 254.05),  Boilerplate::Panel::Pitch, true);
   makeInput(this, Vec(64.55, 254.42),  Boilerplate::Panel::Sync, false);
   makeInput(this, Vec(24.68, 174.23),  Boilerplate::Panel::FM, false);

   makeOutput(this, Vec(65.83, 355.83), Boilerplate::Panel::Out, true);
}

#endif // NOT BoilerplateHPP
