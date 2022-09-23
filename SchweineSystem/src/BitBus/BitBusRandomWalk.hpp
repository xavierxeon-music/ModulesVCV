#ifndef BitBusRandomWalkHPP
#define BitBusRandomWalkHPP

#include "BitBusRandomWalk.h"

#include <SvinOrigin.h>

namespace BitBus
{
   struct RandomWalk::Panel
   {
      enum ParamId
      {
         // buttons
         Down = 0,
         Up = 1,
         // switches
         // ledbuttons
         // knobs
         // sliders
         Mix = 2,
         PARAMS_LEN = 3
      };

      enum DisplayId
      {
         // lcd
         Text_Bank = 0,
         // oled
         DISPLAYS_LEN = 1
      };

      enum MeterId
      {
         METERS_LEN = 0
      };

      enum InputId
      {
         Scan = 0,
         INPUTS_LEN = 1
      };

      enum OutputId
      {
         OUTPUTS_LEN = 0
      };

      enum LightId
      {
         // leds
         RGB_BusIn = 0,
         RGB_BusOut = 3,
         // ledbuttons
         // sliders
         RGB_Mix = 6,
         LIGHTS_LEN = 9
      };

   };

   void RandomWalk::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

      configButton(Panel::Down, "Down");
      configButton(Panel::Up, "Up");

      configSwitch(Panel::Mix, 0.0f, 1.0f, 0.0f, "Mix");

      configInput(Panel::Scan, "Scan");
   }

   void RandomWalkWidget::setup()
   {
      makePanel("res/BitBus/BitBusRandomWalk.svg");

      makeButton(this, Vec(45.44, 255.81), RandomWalk::Panel::Down);
      makeButton(this, Vec(45.44, 210.30), RandomWalk::Panel::Up);

      makeSlider(this, Vec(45.00, 138.86), RandomWalk::Panel::Mix, RandomWalk::Panel::RGB_Mix);

      makeInput(this, Vec(45.00, 320.30),  RandomWalk::Panel::Scan, true);

      makeLED(this, Vec(9.92, 46.77), RandomWalk::Panel::RGB_BusIn);
      makeLED(this, Vec(79.92, 46.77), RandomWalk::Panel::RGB_BusOut);

      makeLCD(this, Vec(20.44, 220.55), 3, RandomWalk::Panel::Text_Bank, 18);
   }
}

#endif // NOT BitBusRandomWalkHPP
