#ifndef HubConnectHPP
#define HubConnectHPP

#include "HubConnect.h"

#include <SvinOrigin.h>

struct HubConnect::Panel
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

void HubConnect::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

void HubConnectWidget::setup()
{
   makePanel("res/Utilities/HubConnect.svg");

   makeLED(this, Vec(30.00, 360.06), HubConnect::Panel::RGB_Connected);
   makeLED(this, Vec(19.03, 280.65), HubConnect::Panel::RGB_NoteC);
   makeLED(this, Vec(24.93, 263.94), HubConnect::Panel::RGB_NoteCs);
   makeLED(this, Vec(19.03, 247.07), HubConnect::Panel::RGB_NoteD);
   makeLED(this, Vec(24.93, 230.36), HubConnect::Panel::RGB_NoteDs);
   makeLED(this, Vec(19.03, 213.49), HubConnect::Panel::RGB_NoteE);
   makeLED(this, Vec(19.03, 198.40), HubConnect::Panel::RGB_NoteF);
   makeLED(this, Vec(24.93, 181.69), HubConnect::Panel::RGB_NoteFs);
   makeLED(this, Vec(19.03, 164.82), HubConnect::Panel::RGB_NoteG);
   makeLED(this, Vec(24.93, 148.11), HubConnect::Panel::RGB_NoteGs);
   makeLED(this, Vec(19.03, 131.24), HubConnect::Panel::RGB_NoteA);
   makeLED(this, Vec(24.93, 114.52), HubConnect::Panel::RGB_NoteAs);
   makeLED(this, Vec(19.03, 97.65), HubConnect::Panel::RGB_NoteB);
}

#endif // NOT HubConnectHPP
