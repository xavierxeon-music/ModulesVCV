#ifndef BefacoACDCHPP
#define BefacoACDCHPP

#include "BefacoACDC.h"

#include <SvinOrigin.h>

struct BefacoACDC::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Connect = 0,
      // knobs
      // sliders
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
      Value_D = 0,
      Value_C = 1,
      Value_B = 2,
      Value_A = 3,
      METERS_LEN = 4
   };

   enum InputId
   {
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      D = 0,
      C = 1,
      B = 2,
      A = 3,
      OUTPUTS_LEN = 4
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

void BefacoACDC::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configOutput(Panel::D, "D");
   configOutput(Panel::C, "C");
   configOutput(Panel::B, "B");
   configOutput(Panel::A, "A");
}

void BefacoACDCWidget::setup()
{
   makePanel("res/Hardware/BefacoACDC.svg");

   makeLEDButton(this, Vec(30.00, 339.33), BefacoACDC::Panel::Connect, BefacoACDC::Panel::RGB_Connect);

   makeOutput(this, Vec(25.59, 256.64), BefacoACDC::Panel::D, false);
   makeOutput(this, Vec(25.59, 205.31), BefacoACDC::Panel::C, false);
   makeOutput(this, Vec(25.59, 153.98), BefacoACDC::Panel::B, false);
   makeOutput(this, Vec(25.59, 102.66), BefacoACDC::Panel::A, false);

   makeMeter(this, Vec(42.59, 243.64), 5, BefacoACDC::Panel::Value_D);
   makeMeter(this, Vec(42.59, 192.31), 5, BefacoACDC::Panel::Value_C);
   makeMeter(this, Vec(42.59, 140.98), 5, BefacoACDC::Panel::Value_B);
   makeMeter(this, Vec(42.59, 89.66), 5, BefacoACDC::Panel::Value_A);
}

#endif // NOT BefacoACDCHPP
