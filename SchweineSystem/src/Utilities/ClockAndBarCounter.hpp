#ifndef ClockAndBarCounterHPP
#define ClockAndBarCounterHPP

#include "ClockAndBarCounter.h"

#include <SvinOrigin.h>

struct ClockAndBarCounter::Panel
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
      Pixels_Display = 0,
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Override_Reset = 0,
      Override_Clock = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      Reset = 0,
      Clock = 1,
      Running = 2,
      OUTPUTS_LEN = 3
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

void ClockAndBarCounter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Override_Reset, "Override_Reset");
   configInput(Panel::Override_Clock, "Override_Clock");

   configOutput(Panel::Reset, "Reset");
   configOutput(Panel::Clock, "Clock");
   configOutput(Panel::Running, "Running");
}

void ClockAndBarCounterWidget::setup()
{
   makePanel("res/Utilities/ClockAndBarCounter.svg");

   makeLEDButton(this, Vec(60.00, 255.46), ClockAndBarCounter::Panel::Connect, ClockAndBarCounter::Panel::RGB_Connect);

   makeInput(this, Vec(95.83, 303.81), ClockAndBarCounter::Panel::Override_Reset, false);
   makeInput(this, Vec(60.00, 303.57), ClockAndBarCounter::Panel::Override_Clock, false);

   makeOutput(this, Vec(95.83, 355.83), ClockAndBarCounter::Panel::Reset, false);
   makeOutput(this, Vec(60.00, 355.83), ClockAndBarCounter::Panel::Clock, false);
   makeOutput(this, Vec(24.17, 355.83), ClockAndBarCounter::Panel::Running, false);

   makeOLED(this, Vec(17.50, 62.04), ClockAndBarCounter::Panel::Pixels_Display, 83, 170);
}

#endif // NOT ClockAndBarCounterHPP
