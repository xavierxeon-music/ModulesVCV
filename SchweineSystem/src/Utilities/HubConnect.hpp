#ifndef HubConnectHPP
#define HubConnectHPP

#include "HubConnect.h"

#include <SvinOrigin.h>

struct HubConnect::Panel
{
   enum ParamId
   {
      // buttons
      Reset = 0,
      Stop = 1,
      Play = 2,
      // switches
      // ledbuttons
      // knobs
      // sliders
      PARAMS_LEN = 3
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

   configButton(Panel::Reset, "Reset");
   configButton(Panel::Stop, "Stop");
   configButton(Panel::Play, "Play");
}

void HubConnectWidget::setup()
{
   makePanel("res/Utilities/HubConnect.svg");

   makeButton(this, Vec(29.80, 103.68), HubConnect::Panel::Reset);
   makeButton(this, Vec(41.72, 73.20), HubConnect::Panel::Stop);
   makeButton(this, Vec(19.48, 73.20), HubConnect::Panel::Play);

   makeLED(this, Vec(30.00, 360.06), HubConnect::Panel::RGB_Connected);
   makeLED(this, Vec(19.03, 320.67), HubConnect::Panel::RGB_NoteC);
   makeLED(this, Vec(24.93, 303.96), HubConnect::Panel::RGB_NoteCs);
   makeLED(this, Vec(19.03, 287.09), HubConnect::Panel::RGB_NoteD);
   makeLED(this, Vec(24.93, 270.38), HubConnect::Panel::RGB_NoteDs);
   makeLED(this, Vec(19.03, 253.51), HubConnect::Panel::RGB_NoteE);
   makeLED(this, Vec(19.03, 238.43), HubConnect::Panel::RGB_NoteF);
   makeLED(this, Vec(24.93, 221.71), HubConnect::Panel::RGB_NoteFs);
   makeLED(this, Vec(19.03, 204.84), HubConnect::Panel::RGB_NoteG);
   makeLED(this, Vec(24.93, 188.13), HubConnect::Panel::RGB_NoteGs);
   makeLED(this, Vec(19.03, 171.26), HubConnect::Panel::RGB_NoteA);
   makeLED(this, Vec(24.93, 154.55), HubConnect::Panel::RGB_NoteAs);
   makeLED(this, Vec(19.03, 137.68), HubConnect::Panel::RGB_NoteB);
}

#endif // NOT HubConnectHPP
