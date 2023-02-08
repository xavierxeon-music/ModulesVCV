#ifndef NerdSeqHPP
#define NerdSeqHPP

#include "NerdSeq.h"

#include <SvinOrigin.h>

struct NerdSeq::Panel
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
      Gate = 0,
      OUTPUTS_LEN = 1
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

void NerdSeq::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configOutput(Panel::Gate, "Gate");
}

void NerdSeqWidget::setup()
{
   makePanel("res/Hardware/NerdSeq.svg");

   makeLEDButton(this, Vec(30.00, 350.00), NerdSeq::Panel::Connect, NerdSeq::Panel::RGB_Connect);

   makeOutput(this, Vec(30.00, 266.78), NerdSeq::Panel::Gate, true);
}

#endif // NOT NerdSeqHPP
