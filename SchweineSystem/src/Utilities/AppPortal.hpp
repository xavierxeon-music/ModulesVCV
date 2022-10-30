#ifndef AppPortalHPP
#define AppPortalHPP

#include "AppPortal.h"

#include <SvinOrigin.h>

struct AppPortal::Panel
{
   enum ParamId
   {
      // buttons
      Kill = 0,
      Restart = 1,
      DeviceIdDown = 2,
      DeviceIdUp = 3,
      // switches
      Mode = 4,
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 5
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

void AppPortal::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Kill, "Kill");
   configButton(Panel::Restart, "Restart");
   configButton(Panel::DeviceIdDown, "DeviceIdDown");
   configButton(Panel::DeviceIdUp, "DeviceIdUp");

   configSwitch(Panel::Mode, 0.0f, 1.0f, 0.0f, "Mode");
}

void AppPortalWidget::setup()
{
   makePanel("res/Utilities/AppPortal.svg");

   makeButton(this, Vec(68.20, 352.46), AppPortal::Panel::Kill);
   makeButton(this, Vec(26.35, 353.03), AppPortal::Panel::Restart);
   makeButton(this, Vec(45.00, 160.39), AppPortal::Panel::DeviceIdDown);
   makeButton(this, Vec(45.00, 141.74), AppPortal::Panel::DeviceIdUp);

   makeSwitch(this, Vec(45.00, 269.02), AppPortal::Panel::Mode, false);

   makeLED(this, Vec(45.00, 186.18), AppPortal::Panel::RGB_Connected);

   makeOLED(this, Vec(9.00, 39.78), AppPortal::Panel::Pixels_Display, 70, 60);
}

#endif // NOT AppPortalHPP
