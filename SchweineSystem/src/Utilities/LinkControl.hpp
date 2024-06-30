#ifndef LinkControlHPP
#define LinkControlHPP

#include "LinkControl.h"

#include <SvinOrigin.h>

struct LinkControl::Panel
{
   enum ParamId
   {
      // buttons
      Down = 0,
      Up = 1,
      // switches
      // ledbuttons
      Active = 2,
      // knobs
      // sliders
      PARAMS_LEN = 3
   };

   enum DisplayId
   {
      // lcd
      Text_Tempo = 0,
      // oled
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_Connected = 0,
      RGB_NoteC = 3,
      RGB_NoteCs = 6,
      RGB_NoteD = 9,
      RGB_NoteDs = 12,
      RGB_NoteE = 15,
      RGB_NoteF = 18,
      RGB_NoteFs = 21,
      RGB_NoteG = 24,
      RGB_NoteGs = 27,
      RGB_NoteA = 30,
      RGB_NoteAs = 33,
      RGB_NoteB = 36,
      // ledbuttons
      RGB_Active = 39,
      // sliders
      LIGHTS_LEN = 42
   };

};

void LinkControl::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Down, "Down");
   configButton(Panel::Up, "Up");

   configButton(Panel::Active, "Active");
}

void LinkControlWidget::setup()
{
   makePanel("res/Utilities/LinkControl.svg");

   makeButton(this, Vec(51.93, 336.85), LinkControl::Panel::Down);
   makeButton(this, Vec(51.93, 320.02), LinkControl::Panel::Up);

   makeLEDButton(this, Vec(27.60, 326.95), LinkControl::Panel::Active, LinkControl::Panel::RGB_Active);

   makeLED(this, Vec(37.50, 366.18), LinkControl::Panel::RGB_Connected);
   makeLED(this, Vec(26.53, 252.12), LinkControl::Panel::RGB_NoteC);
   makeLED(this, Vec(32.43, 235.40), LinkControl::Panel::RGB_NoteCs);
   makeLED(this, Vec(26.53, 218.53), LinkControl::Panel::RGB_NoteD);
   makeLED(this, Vec(32.43, 201.82), LinkControl::Panel::RGB_NoteDs);
   makeLED(this, Vec(26.53, 184.95), LinkControl::Panel::RGB_NoteE);
   makeLED(this, Vec(26.53, 169.87), LinkControl::Panel::RGB_NoteF);
   makeLED(this, Vec(32.43, 153.15), LinkControl::Panel::RGB_NoteFs);
   makeLED(this, Vec(26.53, 136.28), LinkControl::Panel::RGB_NoteG);
   makeLED(this, Vec(32.43, 119.57), LinkControl::Panel::RGB_NoteGs);
   makeLED(this, Vec(26.53, 102.70), LinkControl::Panel::RGB_NoteA);
   makeLED(this, Vec(32.43, 85.99), LinkControl::Panel::RGB_NoteAs);
   makeLED(this, Vec(26.53, 69.12), LinkControl::Panel::RGB_NoteB);

   makeLCD(this, Vec(12.50, 284.48), 3, LinkControl::Panel::Text_Tempo, 18);
}

#endif // NOT LinkControlHPP
