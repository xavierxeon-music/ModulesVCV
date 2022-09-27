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
      // ledbuttons
      Loop = 1,
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
      Upload = 0,
      Group2_Pass = 1,
      Group1_Pass = 2,
      INPUTS_LEN = 3
   };

   enum OutputId
   {
      Group2_Output = 0,
      Group1_Output = 1,
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

void Maestro::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Mode, "Mode");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::Upload, "Upload");
   configInput(Panel::Group2_Pass, "Group2_Pass");
   configInput(Panel::Group1_Pass, "Group1_Pass");

   configOutput(Panel::Group2_Output, "Group2_Output");
   configOutput(Panel::Group1_Output, "Group1_Output");
}

void MaestroWidget::setup()
{
   makePanel("res/Sequencer/Maestro.svg");

   makeButton(this, Vec(97.56, 232.00), Maestro::Panel::Mode);

   makeLEDButton(this, Vec(43.21, 232.00), Maestro::Panel::Loop, Maestro::Panel::RGB_Loop);

   makeInput(this, Vec(95.83, 355.81),  Maestro::Panel::Upload, false);
   makeInput(this, Vec(24.17, 302.21),  Maestro::Panel::Group2_Pass, true);
   makeInput(this, Vec(24.17, 268.71),  Maestro::Panel::Group1_Pass, true);

   makeOutput(this, Vec(95.83, 302.21), Maestro::Panel::Group2_Output, true);
   makeOutput(this, Vec(95.83, 268.71), Maestro::Panel::Group1_Output, true);

   makeOLED(this, Vec(9.00, 32.00), Maestro::Panel::Pixels_Display, 100, 180);
}

#endif // NOT MaestroHPP
