#ifndef MeshStackHPP
#define MeshStackHPP

#include "MeshStack.h"

#include <SvinOrigin.h>

struct MeshStack::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      Mode = 0,
      // sliders
      Blue = 1,
      Green = 2,
      Red = 3,
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
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      Out = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      RGB_Color = 0,
      // ledbuttons
      // sliders
      RGB_Blue = 3,
      RGB_Green = 6,
      RGB_Red = 9,
      LIGHTS_LEN = 12
   };

};

void MeshStack::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Blue, 0.0f, 1.0f, 0.0f, "Blue");
   configSwitch(Panel::Green, 0.0f, 1.0f, 0.0f, "Green");
   configSwitch(Panel::Red, 0.0f, 1.0f, 0.0f, "Red");

   configParam(Panel::Mode, -1.f, 1.f, 0.f, "Mode");

   configInput(Panel::Pitch, "Pitch");

   configOutput(Panel::Out, "Out");
}

void MeshStackWidget::setup()
{
   makePanel("res/Synths/MeshStack.svg");

   makeSlider(this, Vec(83.74, 147.50), MeshStack::Panel::Blue, MeshStack::Panel::RGB_Blue);
   makeSlider(this, Vec(68.50, 147.50), MeshStack::Panel::Green, MeshStack::Panel::RGB_Green);
   makeSlider(this, Vec(53.26, 147.50), MeshStack::Panel::Red, MeshStack::Panel::RGB_Red);

   makeKnob(this, Vec(216.14, 319.36), MeshStack::Panel::Mode, 3);

   makeInput(this, Vec(94.38, 290.07),  MeshStack::Panel::Pitch, false);

   makeOutput(this, Vec(94.38, 332.98), MeshStack::Panel::Out, false);

   makeLED(this, Vec(105.25, 147.50), MeshStack::Panel::RGB_Color);
}

#endif // NOT MeshStackHPP
