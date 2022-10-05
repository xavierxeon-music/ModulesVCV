#ifndef DrumTriggerHPP
#define DrumTriggerHPP

#include "DrumTrigger.h"

#include <SvinOrigin.h>

struct DrumTrigger::Panel
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
      Input = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Connect = 0,
      // sliders
      LIGHTS_LEN = 3
   };

};

void DrumTrigger::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Input, "Input");
}

void DrumTriggerWidget::setup()
{
   makePanel("res/Hardware/DrumTrigger.svg");

   makeLEDButton(this, Vec(30.00, 349.57), DrumTrigger::Panel::Connect, DrumTrigger::Panel::RGB_Connect);

   makeInput(this, Vec(30.00, 263.12),  DrumTrigger::Panel::Input, true);
}

#endif // NOT DrumTriggerHPP
