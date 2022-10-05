#ifndef GateKeeperHPP
#define GateKeeperHPP

#include "GateKeeper.h"

#include <SvinOrigin.h>

struct GateKeeper::Panel
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
      Pass = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      One_Output = 0,
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

void GateKeeper::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::BankDown, "BankDown");
   configButton(Panel::BankUp, "BankUp");
   configButton(Panel::Mode, "Mode");

   configSwitch(Panel::NoOffset, 0.0f, 1.0f, 0.0f, "NoOffset");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::Pass, "Pass");

   configOutput(Panel::One_Output, "One_Output");
}

void GateKeeperWidget::setup()
{
   makePanel("res/Sequencer/GateKeeper.svg");

   makeButton(this, Vec(98.09, 204.79), GateKeeper::Panel::BankDown);
   makeButton(this, Vec(98.09, 186.15), GateKeeper::Panel::BankUp);
   makeButton(this, Vec(55.25, 185.83), GateKeeper::Panel::Mode);

   makeSwitch(this, Vec(49.56, 355.83), GateKeeper::Panel::NoOffset, false);

   makeLEDButton(this, Vec(75.00, 270.80), GateKeeper::Panel::Loop, GateKeeper::Panel::RGB_Loop);

   makeInput(this, Vec(24.17, 355.83),  GateKeeper::Panel::Pass, true);

   makeOutput(this, Vec(125.83, 355.83), GateKeeper::Panel::One_Output, true);

   makeOLED(this, Vec(9.00, 32.00), GateKeeper::Panel::Pixels_Display, 130, 120);
}

#endif // NOT GateKeeperHPP
