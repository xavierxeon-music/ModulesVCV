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
      Offset = 3,
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
      Upload = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      Eight_Output = 0,
      Seven_Output = 1,
      Six_Output = 2,
      Five_Output = 3,
      Four_Output = 4,
      Three_Output = 5,
      Two_Output = 6,
      One_Output = 7,
      OUTPUTS_LEN = 8
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

   configSwitch(Panel::Offset, 0.0f, 1.0f, 0.0f, "Offset");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::Pass, "Pass");
   configInput(Panel::Upload, "Upload");

   configOutput(Panel::Eight_Output, "Eight_Output");
   configOutput(Panel::Seven_Output, "Seven_Output");
   configOutput(Panel::Six_Output, "Six_Output");
   configOutput(Panel::Five_Output, "Five_Output");
   configOutput(Panel::Four_Output, "Four_Output");
   configOutput(Panel::Three_Output, "Three_Output");
   configOutput(Panel::Two_Output, "Two_Output");
   configOutput(Panel::One_Output, "One_Output");
}

void GateKeeperWidget::setup()
{
   makePanel("res/Sequencer/GateKeeper.svg");

   makeButton(this, Vec(112.64, 207.02), GateKeeper::Panel::BankDown);
   makeButton(this, Vec(112.64, 188.37), GateKeeper::Panel::BankUp);
   makeButton(this, Vec(40.71, 188.37), GateKeeper::Panel::Mode);

   makeSwitch(this, Vec(46.67, 355.40), GateKeeper::Panel::Offset, false);

   makeLEDButton(this, Vec(24.17, 249.48), GateKeeper::Panel::Loop, GateKeeper::Panel::RGB_Loop);

   makeInput(this, Vec(24.17, 355.83),  GateKeeper::Panel::Pass, true);
   makeInput(this, Vec(24.17, 305.92),  GateKeeper::Panel::Upload, false);

   makeOutput(this, Vec(125.83, 355.83), GateKeeper::Panel::Eight_Output, true);
   makeOutput(this, Vec(125.83, 317.16), GateKeeper::Panel::Seven_Output, true);
   makeOutput(this, Vec(125.83, 278.50), GateKeeper::Panel::Six_Output, true);
   makeOutput(this, Vec(125.83, 239.84), GateKeeper::Panel::Five_Output, true);
   makeOutput(this, Vec(85.70, 355.83), GateKeeper::Panel::Four_Output, true);
   makeOutput(this, Vec(85.70, 317.16), GateKeeper::Panel::Three_Output, true);
   makeOutput(this, Vec(85.70, 278.50), GateKeeper::Panel::Two_Output, true);
   makeOutput(this, Vec(85.70, 239.84), GateKeeper::Panel::One_Output, true);

   makeOLED(this, Vec(9.00, 32.00), GateKeeper::Panel::Pixels_Display, 130, 120);
}

#endif // NOT GateKeeperHPP
