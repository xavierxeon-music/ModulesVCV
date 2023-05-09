#ifndef MaestroHPP
#define MaestroHPP

#include "Maestro.h"

#include <SvinOrigin.h>

struct Maestro::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      NoOffset = 0,
      // ledbuttons
      Connect = 1,
      Loop = 2,
      ModeReplay = 3,
      ModeRemote = 4,
      ModePass = 5,
      DisplayContour = 6,
      DisplayMelody = 7,
      DisplayGroove = 8,
      DisplayOverview = 9,
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
      ContourPass = 0,
      GatePass = 1,
      Upload = 2,
      INPUTS_LEN = 3
   };

   enum OutputId
   {
      ContourOutput = 0,
      GateOutput = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Connect = 0,
      RGB_Loop = 3,
      RGB_ModeReplay = 6,
      RGB_ModeRemote = 9,
      RGB_ModePass = 12,
      RGB_DisplayContour = 15,
      RGB_DisplayMelody = 18,
      RGB_DisplayGroove = 21,
      RGB_DisplayOverview = 24,
      // sliders
      LIGHTS_LEN = 27
   };

};

void Maestro::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::NoOffset, 0.0f, 1.0f, 0.0f, "NoOffset");

   configButton(Panel::Connect, "Connect");
   configButton(Panel::Loop, "Loop");
   configButton(Panel::ModeReplay, "ModeReplay");
   configButton(Panel::ModeRemote, "ModeRemote");
   configButton(Panel::ModePass, "ModePass");
   configButton(Panel::DisplayContour, "DisplayContour");
   configButton(Panel::DisplayMelody, "DisplayMelody");
   configButton(Panel::DisplayGroove, "DisplayGroove");
   configButton(Panel::DisplayOverview, "DisplayOverview");

   configInput(Panel::ContourPass, "ContourPass");
   configInput(Panel::GatePass, "GatePass");
   configInput(Panel::Upload, "Upload");

   configOutput(Panel::ContourOutput, "ContourOutput");
   configOutput(Panel::GateOutput, "GateOutput");
}

void MaestroWidget::setup()
{
   makePanel("res/Sequencer/Maestro.svg");

   makeSwitch(this, Vec(98.67, 300.80), Maestro::Panel::NoOffset, false);

   makeLEDButton(this, Vec(73.05, 248.72), Maestro::Panel::Connect, Maestro::Panel::RGB_Connect);
   makeLEDButton(this, Vec(146.12, 248.72), Maestro::Panel::Loop, Maestro::Panel::RGB_Loop);
   makeLEDButton(this, Vec(22.00, 186.69), Maestro::Panel::ModeReplay, Maestro::Panel::RGB_ModeReplay);
   makeLEDButton(this, Vec(22.00, 151.60), Maestro::Panel::ModeRemote, Maestro::Panel::RGB_ModeRemote);
   makeLEDButton(this, Vec(22.00, 117.03), Maestro::Panel::ModePass, Maestro::Panel::RGB_ModePass);
   makeLEDButton(this, Vec(156.47, 55.56), Maestro::Panel::DisplayContour, Maestro::Panel::RGB_DisplayContour);
   makeLEDButton(this, Vec(121.49, 55.96), Maestro::Panel::DisplayMelody, Maestro::Panel::RGB_DisplayMelody);
   makeLEDButton(this, Vec(86.52, 55.56), Maestro::Panel::DisplayGroove, Maestro::Panel::RGB_DisplayGroove);
   makeLEDButton(this, Vec(51.54, 55.56), Maestro::Panel::DisplayOverview, Maestro::Panel::RGB_DisplayOverview);

   makeInput(this, Vec(57.26, 344.87),  Maestro::Panel::ContourPass, true);
   makeInput(this, Vec(56.91, 300.94),  Maestro::Panel::GatePass, true);
   makeInput(this, Vec(104.17, 345.35),  Maestro::Panel::Upload, false);

   makeOutput(this, Vec(155.83, 344.86), Maestro::Panel::ContourOutput, true);
   makeOutput(this, Vec(155.48, 301.44), Maestro::Panel::GateOutput, true);

   makeOLED(this, Vec(38.00, 70.78), Maestro::Panel::Pixels_Display, 130, 150);
}

#endif // NOT MaestroHPP
