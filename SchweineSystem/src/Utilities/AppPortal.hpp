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
      GateInput = 0,
      PitchInput = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      GateOutput = 0,
      OUTPUTS_LEN = 1
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

   configInput(Panel::GateInput, "GateInput");
   configInput(Panel::PitchInput, "PitchInput");

   configOutput(Panel::GateOutput, "GateOutput");
}

void AppPortalWidget::setup()
{
   makePanel("res/Utilities/AppPortal.svg");

   makeButton(this, Vec(66.24, 251.14), AppPortal::Panel::Kill);
   makeButton(this, Vec(24.39, 251.71), AppPortal::Panel::Restart);
   makeButton(this, Vec(66.24, 167.21), AppPortal::Panel::DeviceIdDown);
   makeButton(this, Vec(66.24, 148.56), AppPortal::Panel::DeviceIdUp);

   makeSwitch(this, Vec(23.99, 163.04), AppPortal::Panel::Mode, false);

   makeInput(this, Vec(24.17, 355.83), AppPortal::Panel::GateInput, true);
   makeInput(this, Vec(24.17, 308.49), AppPortal::Panel::PitchInput, true);

   makeOutput(this, Vec(65.83, 355.57), AppPortal::Panel::GateOutput, true);

   makeLED(this, Vec(66.24, 193.00), AppPortal::Panel::RGB_Connected);

   makeOLED(this, Vec(9.00, 39.78), AppPortal::Panel::Pixels_Display, 70, 60);
}

#endif // NOT AppPortalHPP
