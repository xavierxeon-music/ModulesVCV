#ifndef GrooveMaestroHPP
#define GrooveMaestroHPP

#include "GrooveMaestro.h"

#include <SvinOrigin.h>

struct GrooveMaestro::Panel
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

void GrooveMaestro::setup()
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

void GrooveMaestroWidget::setup()
{
   makePanel("res/Sequencer/GrooveMaestro.svg");

   makeButton(this, Vec(27.55, 68.92), GrooveMaestro::Panel::Mode);

   makeSwitch(this, Vec(121.40, 355.83), GrooveMaestro::Panel::NoOffset, false);

   makeLEDButton(this, Vec(27.32, 267.06), GrooveMaestro::Panel::Loop, GrooveMaestro::Panel::RGB_Loop);
   makeLEDButton(this, Vec(27.55, 177.57), GrooveMaestro::Panel::Connect, GrooveMaestro::Panel::RGB_Connect);

   makeInput(this, Vec(96.01, 355.83),  GrooveMaestro::Panel::GatePass, true);
   makeInput(this, Vec(96.01, 310.33),  GrooveMaestro::Panel::ContourPass, true);
   makeInput(this, Vec(24.17, 355.83),  GrooveMaestro::Panel::Upload, false);

   makeOutput(this, Vec(170.49, 355.83), GrooveMaestro::Panel::GateOutput, true);
   makeOutput(this, Vec(170.49, 310.33), GrooveMaestro::Panel::ContourOutput, true);

   makeLCD(this, Vec(10.00, 135.68), 2, GrooveMaestro::Panel::Text_DeviceId, 18);

   makeOLED(this, Vec(53.00, 31.79), GrooveMaestro::Panel::Pixels_Display, 130, 250);
}

#endif // NOT GrooveMaestroHPP
