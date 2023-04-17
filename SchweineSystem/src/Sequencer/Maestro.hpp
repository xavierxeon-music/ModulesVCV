#ifndef MaestroHPP
#define MaestroHPP

#include "Maestro.h"

#include <SvinOrigin.h>

struct Maestro::Panel
{
   enum ParamId
   {
      // buttons
      Mode = 0,
      // switches
      NoOffset = 1,
      // ledbuttons
      Loop = 2,
      Connect = 3,
      // knobs
      // sliders
      PARAMS_LEN = 4
   };

   enum DisplayId
   {
      // lcd
      Text_DeviceId = 0,
      // oled
      Pixels_Display = 1,
      DISPLAYS_LEN = 2
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      GatePass = 0,
      ContourPass = 1,
      Upload = 2,
      INPUTS_LEN = 3
   };

   enum OutputId
   {
      GateOutput = 0,
      ContourOutput = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Loop = 0,
      RGB_Connect = 3,
      // sliders
      LIGHTS_LEN = 6
   };
};

void Maestro::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Mode, "Mode");

   configSwitch(Panel::NoOffset, 0.0f, 1.0f, 0.0f, "NoOffset");

   configButton(Panel::Loop, "Loop");
   configButton(Panel::Connect, "Connect");

   configInput(Panel::GatePass, "GatePass");
   configInput(Panel::ContourPass, "ContourPass");
   configInput(Panel::Upload, "Upload");

   configOutput(Panel::GateOutput, "GateOutput");
   configOutput(Panel::ContourOutput, "ContourOutput");
}

void MaestroWidget::setup()
{
   makePanel("res/Sequencer/Maestro.svg");

   makeButton(this, Vec(27.55, 68.92), Maestro::Panel::Mode);

   makeSwitch(this, Vec(121.40, 355.83), Maestro::Panel::NoOffset, false);

   makeLEDButton(this, Vec(27.32, 267.06), Maestro::Panel::Loop, Maestro::Panel::RGB_Loop);
   makeLEDButton(this, Vec(27.55, 177.57), Maestro::Panel::Connect, Maestro::Panel::RGB_Connect);

   makeInput(this, Vec(96.01, 355.83), Maestro::Panel::GatePass, true);
   makeInput(this, Vec(96.01, 310.33), Maestro::Panel::ContourPass, true);
   makeInput(this, Vec(24.17, 355.83), Maestro::Panel::Upload, false);

   makeOutput(this, Vec(170.49, 355.83), Maestro::Panel::GateOutput, true);
   makeOutput(this, Vec(170.49, 310.33), Maestro::Panel::ContourOutput, true);

   makeLCD(this, Vec(10.00, 135.68), 2, Maestro::Panel::Text_DeviceId, 18);

   makeOLED(this, Vec(53.00, 31.79), Maestro::Panel::Pixels_Display, 130, 250);
}

#endif // NOT MaestroHPP
