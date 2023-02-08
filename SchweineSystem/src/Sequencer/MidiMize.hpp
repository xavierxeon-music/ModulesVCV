#ifndef MidiMizeHPP
#define MidiMizeHPP

#include "MidiMize.h"

#include <SvinOrigin.h>

struct MidiMize::Panel
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
      Velocity = 0,
      Gate = 1,
      Pitch = 2,
      INPUTS_LEN = 3
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      LIGHTS_LEN = 0
   };

};

void MidiMize::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Velocity, "Velocity");
   configInput(Panel::Gate, "Gate");
   configInput(Panel::Pitch, "Pitch");
}

void MidiMizeWidget::setup()
{
   makePanel("res/Sequencer/MidiMize.svg");

   makeInput(this, Vec(30.00, 309.00),  MidiMize::Panel::Velocity, true);
   makeInput(this, Vec(30.00, 262.18),  MidiMize::Panel::Gate, true);
   makeInput(this, Vec(30.00, 215.52),  MidiMize::Panel::Pitch, true);
}

#endif // NOT MidiMizeHPP
