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
      Connect = 0,
      // knobs
      // sliders
      PARAMS_LEN = 1
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
      RGB_Connect = 36,
      // sliders
      LIGHTS_LEN = 39
   };

};

void HubConnect::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");
}

void HubConnectWidget::setup()
{
   makePanel("res/Utilities/HubConnect.svg");

   makeLEDButton(this, Vec(30.00, 350.06), HubConnect::Panel::Connect, HubConnect::Panel::RGB_Connect);

   makeLED(this, Vec(19.03, 290.67), HubConnect::Panel::RGB_NoteC);
   makeLED(this, Vec(24.93, 279.04), HubConnect::Panel::RGB_NoteCs);
   makeLED(this, Vec(19.03, 267.40), HubConnect::Panel::RGB_NoteD);
   makeLED(this, Vec(24.93, 255.77), HubConnect::Panel::RGB_NoteDs);
   makeLED(this, Vec(19.03, 244.13), HubConnect::Panel::RGB_NoteE);
   makeLED(this, Vec(19.03, 232.49), HubConnect::Panel::RGB_NoteF);
   makeLED(this, Vec(24.93, 220.86), HubConnect::Panel::RGB_NoteFs);
   makeLED(this, Vec(19.03, 209.22), HubConnect::Panel::RGB_NoteG);
   makeLED(this, Vec(24.93, 197.58), HubConnect::Panel::RGB_NoteGs);
   makeLED(this, Vec(19.03, 185.95), HubConnect::Panel::RGB_NoteA);
   makeLED(this, Vec(24.93, 174.31), HubConnect::Panel::RGB_NoteAs);
   makeLED(this, Vec(19.03, 162.68), HubConnect::Panel::RGB_NoteB);
}

#endif // NOT HubConnectHPP
