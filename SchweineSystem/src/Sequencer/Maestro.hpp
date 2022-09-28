#ifndef MaestroHPP
#define MaestroHPP

#include "Maestro.h"

#include <SvinOrigin.h>

struct Maestro::Panel
{
   enum ParamId
   {
      // buttons
      BankDown = 0,
      BankUp = 1,
      Mode = 2,
      // switches
      // ledbuttons
      Loop = 3,
      // knobs
      // sliders
      PARAMS_LEN = 4
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
      Pass = 0,
      Upload = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      Output = 0,
      OUTPUTS_LEN = 1
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

void Maestro::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::BankDown, "BankDown");
   configButton(Panel::BankUp, "BankUp");
   configButton(Panel::Mode, "Mode");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::Pass, "Pass");
   configInput(Panel::Upload, "Upload");

   configOutput(Panel::Output, "Output");
}

void MaestroWidget::setup()
{
   makePanel("res/Sequencer/Maestro.svg");

   makeButton(this, Vec(95.85, 261.47), Maestro::Panel::BankDown);
   makeButton(this, Vec(95.85, 242.82), Maestro::Panel::BankUp);
   makeButton(this, Vec(23.93, 242.82), Maestro::Panel::Mode);

   makeLEDButton(this, Vec(60.00, 354.73), Maestro::Panel::Loop, Maestro::Panel::RGB_Loop);

   makeInput(this, Vec(24.17, 355.83), Maestro::Panel::Pass, true);
   makeInput(this, Vec(60.00, 249.04), Maestro::Panel::Upload, false);

   makeOutput(this, Vec(95.83, 355.83), Maestro::Panel::Output, true);

   makeOLED(this, Vec(9.00, 32.00), Maestro::Panel::Pixels_Display, 100, 180);
}

#endif // NOT MaestroHPP
