#ifndef LinkControlHPP
#define LinkControlHPP

#include "LinkControl.h"

#include <SvinOrigin.h>

struct LinkControl::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 0
   };

   enum DisplayId
   {
      // lcd
      // oled
      DISPLAYS_LEN = 0
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
      // sliders
      LIGHTS_LEN = 39
   };

};

void LinkControl::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

void LinkControlWidget::setup()
{
   makePanel("res/Utilities/LinkControl.svg");

   makeLED(this, Vec(30.00, 360.06), LinkControl::Panel::RGB_Connected);
   makeLED(this, Vec(19.03, 280.65), LinkControl::Panel::RGB_NoteC);
   makeLED(this, Vec(24.93, 263.94), LinkControl::Panel::RGB_NoteCs);
   makeLED(this, Vec(19.03, 247.07), LinkControl::Panel::RGB_NoteD);
   makeLED(this, Vec(24.93, 230.36), LinkControl::Panel::RGB_NoteDs);
   makeLED(this, Vec(19.03, 213.49), LinkControl::Panel::RGB_NoteE);
   makeLED(this, Vec(19.03, 198.40), LinkControl::Panel::RGB_NoteF);
   makeLED(this, Vec(24.93, 181.69), LinkControl::Panel::RGB_NoteFs);
   makeLED(this, Vec(19.03, 164.82), LinkControl::Panel::RGB_NoteG);
   makeLED(this, Vec(24.93, 148.11), LinkControl::Panel::RGB_NoteGs);
   makeLED(this, Vec(19.03, 131.24), LinkControl::Panel::RGB_NoteA);
   makeLED(this, Vec(24.93, 114.52), LinkControl::Panel::RGB_NoteAs);
   makeLED(this, Vec(19.03, 97.65), LinkControl::Panel::RGB_NoteB);
}

#endif // NOT LinkControlHPP
