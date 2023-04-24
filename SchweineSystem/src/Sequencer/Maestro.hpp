#ifndef MaestroHPP
#define MaestroHPP

#include "Maestro.h"

#include <SvinOrigin.h>

struct Maestro::Panel
{
   enum ParamId
   {
      // buttons
      ModeReplay = 0,
      ModeRemote = 1,
      ModePass = 2,
      DisplayContour = 3,
      DisplayMelody = 4,
      DisplayGroove = 5,
      DisplayOverview = 6,
      // switches
      NoOffset = 7,
      // ledbuttons
      Connect = 8,
      Loop = 9,
      // knobs
      // sliders
      PARAMS_LEN = 10
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
      RGB_Connect = 0,
      RGB_Loop = 3,
      // sliders
      LIGHTS_LEN = 6
   };

};

void Maestro::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::ModeReplay, "ModeReplay");
   configButton(Panel::ModeRemote, "ModeRemote");
   configButton(Panel::ModePass, "ModePass");
   configButton(Panel::DisplayContour, "DisplayContour");
   configButton(Panel::DisplayMelody, "DisplayMelody");
   configButton(Panel::DisplayGroove, "DisplayGroove");
   configButton(Panel::DisplayOverview, "DisplayOverview");

   configSwitch(Panel::NoOffset, 0.0f, 1.0f, 0.0f, "NoOffset");

   configButton(Panel::Connect, "Connect");
   configButton(Panel::Loop, "Loop");

   configInput(Panel::GatePass, "GatePass");
   configInput(Panel::ContourPass, "ContourPass");
   configInput(Panel::Upload, "Upload");

   configOutput(Panel::GateOutput, "GateOutput");
   configOutput(Panel::ContourOutput, "ContourOutput");
}

void MaestroWidget::setup()
{
   makePanel("res/Sequencer/Maestro.svg");

   makeButton(this, Vec(23.96, 182.17), Maestro::Panel::ModeReplay);
   makeButton(this, Vec(23.96, 147.08), Maestro::Panel::ModeRemote);
   makeButton(this, Vec(23.96, 112.51), Maestro::Panel::ModePass);
   makeButton(this, Vec(156.48, 60.58), Maestro::Panel::DisplayContour);
   makeButton(this, Vec(121.51, 60.98), Maestro::Panel::DisplayMelody);
   makeButton(this, Vec(86.53, 60.58), Maestro::Panel::DisplayGroove);
   makeButton(this, Vec(51.56, 60.58), Maestro::Panel::DisplayOverview);

   makeSwitch(this, Vec(98.67, 300.80), Maestro::Panel::NoOffset, false);

   makeLEDButton(this, Vec(76.11, 250.63), Maestro::Panel::Connect, Maestro::Panel::RGB_Connect);
   makeLEDButton(this, Vec(143.07, 249.87), Maestro::Panel::Loop, Maestro::Panel::RGB_Loop);

   makeInput(this, Vec(56.91, 300.94),  Maestro::Panel::GatePass, true);
   makeInput(this, Vec(57.26, 344.87),  Maestro::Panel::ContourPass, true);
   makeInput(this, Vec(104.17, 345.35),  Maestro::Panel::Upload, false);

   makeOutput(this, Vec(155.48, 301.44), Maestro::Panel::GateOutput, true);
   makeOutput(this, Vec(155.83, 344.86), Maestro::Panel::ContourOutput, true);

   makeOLED(this, Vec(38.00, 70.78), Maestro::Panel::Pixels_Display, 130, 150);
}

#endif // NOT MaestroHPP
