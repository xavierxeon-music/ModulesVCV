#ifndef DrumTriggerHPP
#define DrumTriggerHPP

#include "DrumTrigger.h"

#include <SvinOrigin.h>

struct DrumTrigger::Panel
{
   enum ParamId
   {
      // buttons
      Device = 0,
      // switches
      // ledbuttons
      Connect = 1,
      // knobs
      // sliders
      PARAMS_LEN = 2
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
      RGB_BitBoxMini = 0,
      RGB_BitBox2 = 3,
      RGB_Erika = 6,
      // ledbuttons
      RGB_Connect = 9,
      // sliders
      LIGHTS_LEN = 12
   };

};

void DrumTrigger::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Device, "Device");

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Input, "Input");
}

void DrumTriggerWidget::setup()
{
   makePanel("res/Hardware/DrumTrigger.svg");

   makeButton(this, Vec(30.12, 93.59), DrumTrigger::Panel::Device);

   makeLEDButton(this, Vec(30.00, 350.00), DrumTrigger::Panel::Connect, DrumTrigger::Panel::RGB_Connect);

   makeInput(this, Vec(30.00, 238.69),  DrumTrigger::Panel::Input, true);

   makeLED(this, Vec(15.45, 134.14), DrumTrigger::Panel::RGB_BitBoxMini);
   makeLED(this, Vec(15.45, 122.14), DrumTrigger::Panel::RGB_BitBox2);
   makeLED(this, Vec(15.45, 110.14), DrumTrigger::Panel::RGB_Erika);
}

#endif // NOT DrumTriggerHPP
