#ifndef ScaleShowHPP
#define ScaleShowHPP

#include "ScaleShow.h"

#include <SvinOrigin.h>

struct ScaleShow::Panel
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
      RGB_NoteC = 0,
      RGB_NoteCs = 3,
      RGB_NoteD = 6,
      RGB_NoteDs = 9,
      RGB_NoteE = 12,
      RGB_NoteF = 15,
      RGB_NoteFs = 18,
      RGB_NoteG = 21,
      RGB_NoteGs = 24,
      RGB_NoteA = 27,
      RGB_NoteAs = 30,
      RGB_NoteB = 33,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 36
   };

};

void ScaleShow::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

void ScaleShowWidget::setup()
{
   makePanel("res/Utilities/ScaleShow.svg");

   makeLED(this, Vec(19.11, 326.90), ScaleShow::Panel::RGB_NoteC);
   makeLED(this, Vec(25.01, 310.19), ScaleShow::Panel::RGB_NoteCs);
   makeLED(this, Vec(19.11, 293.32), ScaleShow::Panel::RGB_NoteD);
   makeLED(this, Vec(25.01, 276.60), ScaleShow::Panel::RGB_NoteDs);
   makeLED(this, Vec(19.11, 259.73), ScaleShow::Panel::RGB_NoteE);
   makeLED(this, Vec(19.11, 244.65), ScaleShow::Panel::RGB_NoteF);
   makeLED(this, Vec(25.01, 227.94), ScaleShow::Panel::RGB_NoteFs);
   makeLED(this, Vec(19.11, 211.07), ScaleShow::Panel::RGB_NoteG);
   makeLED(this, Vec(25.01, 194.35), ScaleShow::Panel::RGB_NoteGs);
   makeLED(this, Vec(19.11, 177.48), ScaleShow::Panel::RGB_NoteA);
   makeLED(this, Vec(25.01, 160.77), ScaleShow::Panel::RGB_NoteAs);
   makeLED(this, Vec(19.11, 143.90), ScaleShow::Panel::RGB_NoteB);
}

#endif // NOT ScaleShowHPP
