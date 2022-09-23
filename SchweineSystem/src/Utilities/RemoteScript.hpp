#ifndef RemoteScriptHPP
#define RemoteScriptHPP

#include "RemoteScript.h"

#include <SvinOrigin.h>

struct RemoteScript::Panel
{
   enum ParamId
   {
      // buttons
      Kill = 0,
      Restart = 1,
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 2
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
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_Connected = 0,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 3
   };

};

void RemoteScript::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Kill, "Kill");
   configButton(Panel::Restart, "Restart");
}

void RemoteScriptWidget::setup()
{
   makePanel("res/Utilities/RemoteScript.svg");

   makeButton(this, Vec(29.50, 227.25), RemoteScript::Panel::Kill);
   makeButton(this, Vec(30.00, 170.36), RemoteScript::Panel::Restart);

   makeLED(this, Vec(30.00, 352.32), RemoteScript::Panel::RGB_Connected);

   makeOLED(this, Vec(9.00, 62.34), RemoteScript::Panel::Pixels_Display, 40, 40);
}

#endif // NOT RemoteScriptHPP
