#ifndef MetropolixClockHPP
#define MetropolixClockHPP

#include "MetropolixClock.h"

#include <SvinOrigin.h>

struct MetropolixClock::Panel
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
      OUTPUTS_LEN = 2
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

void MetropolixClock::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Override_Reset, "Override_Reset");
   configInput(Panel::Override_Clock, "Override_Clock");

   configOutput(Panel::Reset, "Reset");
   configOutput(Panel::Clock, "Clock");
}

void MetropolixClockWidget::setup()
{
   makePanel("res/Hardware/MetropolixClock.svg");

   makeLEDButton(this, Vec(76.53, 261.21), MetropolixClock::Panel::Connect, MetropolixClock::Panel::RGB_Connect);

   makeInput(this, Vec(80.83, 308.08),  MetropolixClock::Panel::Override_Reset, false);
   makeInput(this, Vec(41.08, 308.57),  MetropolixClock::Panel::Override_Clock, false);

   makeOutput(this, Vec(80.83, 355.83), MetropolixClock::Panel::Reset, false);
   makeOutput(this, Vec(40.85, 355.83), MetropolixClock::Panel::Clock, false);

   makeOLED(this, Vec(10.00, 61.98), MetropolixClock::Panel::Pixels_Display, 83, 170);
}

#endif // NOT MetropolixClockHPP
