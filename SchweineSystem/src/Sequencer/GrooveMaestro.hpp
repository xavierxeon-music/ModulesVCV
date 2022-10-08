#ifndef GrooveMaestroHPP
#define GrooveMaestroHPP

#include "GrooveMaestro.h"

#include <SvinOrigin.h>

struct GrooveMaestro::Panel
{
   enum ParamId
   {
      // buttons
      BankDown = 0,
      BankUp = 1,
      Mode = 2,
      // switches
      NoOffset = 3,
      // ledbuttons
      Loop = 4,
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
      // sliders
      LIGHTS_LEN = 3
   };

};

void GrooveMaestro::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::BankDown, "BankDown");
   configButton(Panel::BankUp, "BankUp");
   configButton(Panel::Mode, "Mode");

   configSwitch(Panel::NoOffset, 0.0f, 1.0f, 0.0f, "NoOffset");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::GatePass, "GatePass");
   configInput(Panel::ContourPass, "ContourPass");
   configInput(Panel::Upload, "Upload");

   configOutput(Panel::GateOutput, "GateOutput");
   configOutput(Panel::ContourOutput, "ContourOutput");
}

void GrooveMaestroWidget::setup()
{
   makePanel("res/Sequencer/GrooveMaestro.svg");

   makeButton(this, Vec(24.55, 139.76), GrooveMaestro::Panel::BankDown);
   makeButton(this, Vec(24.55, 121.11), GrooveMaestro::Panel::BankUp);
   makeButton(this, Vec(24.55, 68.92), GrooveMaestro::Panel::Mode);

   makeSwitch(this, Vec(121.40, 355.83), GrooveMaestro::Panel::NoOffset, false);

   makeLEDButton(this, Vec(24.17, 222.23), GrooveMaestro::Panel::Loop, GrooveMaestro::Panel::RGB_Loop);

   makeInput(this, Vec(96.01, 355.83),  GrooveMaestro::Panel::GatePass, true);
   makeInput(this, Vec(96.01, 310.33),  GrooveMaestro::Panel::ContourPass, true);
   makeInput(this, Vec(24.17, 355.83),  GrooveMaestro::Panel::Upload, false);

   makeOutput(this, Vec(170.49, 355.83), GrooveMaestro::Panel::GateOutput, true);
   makeOutput(this, Vec(170.49, 310.33), GrooveMaestro::Panel::ContourOutput, true);

   makeOLED(this, Vec(53.00, 31.79), GrooveMaestro::Panel::Pixels_Display, 130, 250);
}

#endif // NOT GrooveMaestroHPP
