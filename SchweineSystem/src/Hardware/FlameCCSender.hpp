#ifndef FlameCCSenderHPP
#define FlameCCSenderHPP

#include "FlameCCSender.h"

#include <SvinOrigin.h>

struct FlameCCSender::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      Half = 0,
      // ledbuttons
      Connect = 1,
      // knobs
      // sliders
      PARAMS_LEN = 2
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
      Voltages = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Connect = 0,
      // sliders
      LIGHTS_LEN = 3
   };

};

void FlameCCSender::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Half, 0.0f, 1.0f, 0.0f, "Half");

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Voltages, "Voltages");
}

void FlameCCSenderWidget::setup()
{
   makePanel("res/Hardware/FlameCCSender.svg");

   makeSwitch(this, Vec(37.78, 194.76), FlameCCSender::Panel::Half, false);

   makeLEDButton(this, Vec(30.00, 350.00), FlameCCSender::Panel::Connect, FlameCCSender::Panel::RGB_Connect);

   makeInput(this, Vec(30.00, 261.36),  FlameCCSender::Panel::Voltages, true);
}

#endif // NOT FlameCCSenderHPP
