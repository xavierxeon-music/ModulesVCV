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
      MeloD_Select = 0,
      MeloC_Select = 1,
      MeloB_Select = 2,
      MeloA_Select = 3,
      // sliders
      PARAMS_LEN = 4
   };

   enum DisplayId
   {
      // lcd
      Text_MeloD_Channel = 0,
      Text_MeloC_Channel = 1,
      Text_MeloB_Channel = 2,
      Text_MeloA_Channel = 3,
      // oled
      DISPLAYS_LEN = 4
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Drums_Eight_Trigger = 0,
      Drums_Four_Trigger = 1,
      Drums_Seven_Trigger = 2,
      Drums_Three_Trigger = 3,
      Drums_Six_Trigger = 4,
      Drums_Two_Trigger = 5,
      Drums_Five_Trigger = 6,
      Drums_One_Trigger = 7,
      MeloD_Velocity = 8,
      MeloD_Gate = 9,
      MeloD_Pitch = 10,
      MeloC_Velocity = 11,
      MeloC_Gate = 12,
      MeloC_Pitch = 13,
      MeloB_Velocity = 14,
      MeloB_Gate = 15,
      MeloB_Pitch = 16,
      MeloA_Velocity = 17,
      MeloA_Gate = 18,
      MeloA_Pitch = 19,
      INPUTS_LEN = 20
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

   configParam(Panel::MeloD_Select, -1.f, 1.f, 0.f, "MeloD_Select");
   configParam(Panel::MeloC_Select, -1.f, 1.f, 0.f, "MeloC_Select");
   configParam(Panel::MeloB_Select, -1.f, 1.f, 0.f, "MeloB_Select");
   configParam(Panel::MeloA_Select, -1.f, 1.f, 0.f, "MeloA_Select");

   configInput(Panel::Drums_Eight_Trigger, "Drums_Eight_Trigger");
   configInput(Panel::Drums_Four_Trigger, "Drums_Four_Trigger");
   configInput(Panel::Drums_Seven_Trigger, "Drums_Seven_Trigger");
   configInput(Panel::Drums_Three_Trigger, "Drums_Three_Trigger");
   configInput(Panel::Drums_Six_Trigger, "Drums_Six_Trigger");
   configInput(Panel::Drums_Two_Trigger, "Drums_Two_Trigger");
   configInput(Panel::Drums_Five_Trigger, "Drums_Five_Trigger");
   configInput(Panel::Drums_One_Trigger, "Drums_One_Trigger");
   configInput(Panel::MeloD_Velocity, "MeloD_Velocity");
   configInput(Panel::MeloD_Gate, "MeloD_Gate");
   configInput(Panel::MeloD_Pitch, "MeloD_Pitch");
   configInput(Panel::MeloC_Velocity, "MeloC_Velocity");
   configInput(Panel::MeloC_Gate, "MeloC_Gate");
   configInput(Panel::MeloC_Pitch, "MeloC_Pitch");
   configInput(Panel::MeloB_Velocity, "MeloB_Velocity");
   configInput(Panel::MeloB_Gate, "MeloB_Gate");
   configInput(Panel::MeloB_Pitch, "MeloB_Pitch");
   configInput(Panel::MeloA_Velocity, "MeloA_Velocity");
   configInput(Panel::MeloA_Gate, "MeloA_Gate");
   configInput(Panel::MeloA_Pitch, "MeloA_Pitch");
}

void MidiMizeWidget::setup()
{
   makePanel("res/Sequencer/MidiMize.svg");

   makeKnob(this, Vec(155.91, 60.61), MidiMize::Panel::MeloD_Select, 1);
   makeKnob(this, Vec(112.09, 60.61), MidiMize::Panel::MeloC_Select, 1);
   makeKnob(this, Vec(68.26, 60.61), MidiMize::Panel::MeloB_Select, 1);
   makeKnob(this, Vec(24.43, 60.61), MidiMize::Panel::MeloA_Select, 1);

   makeInput(this, Vec(155.83, 348.32),  MidiMize::Panel::Drums_Eight_Trigger, false);
   makeInput(this, Vec(155.83, 302.95),  MidiMize::Panel::Drums_Four_Trigger, false);
   makeInput(this, Vec(111.94, 348.32),  MidiMize::Panel::Drums_Seven_Trigger, false);
   makeInput(this, Vec(111.94, 302.95),  MidiMize::Panel::Drums_Three_Trigger, false);
   makeInput(this, Vec(68.06, 348.32),  MidiMize::Panel::Drums_Six_Trigger, false);
   makeInput(this, Vec(68.06, 302.95),  MidiMize::Panel::Drums_Two_Trigger, false);
   makeInput(this, Vec(24.17, 348.32),  MidiMize::Panel::Drums_Five_Trigger, false);
   makeInput(this, Vec(24.17, 302.95),  MidiMize::Panel::Drums_One_Trigger, false);
   makeInput(this, Vec(155.83, 233.16),  MidiMize::Panel::MeloD_Velocity, false);
   makeInput(this, Vec(155.65, 181.86),  MidiMize::Panel::MeloD_Gate, false);
   makeInput(this, Vec(155.65, 131.07),  MidiMize::Panel::MeloD_Pitch, false);
   makeInput(this, Vec(112.00, 233.16),  MidiMize::Panel::MeloC_Velocity, false);
   makeInput(this, Vec(111.83, 181.86),  MidiMize::Panel::MeloC_Gate, false);
   makeInput(this, Vec(111.83, 131.07),  MidiMize::Panel::MeloC_Pitch, false);
   makeInput(this, Vec(68.17, 233.16),  MidiMize::Panel::MeloB_Velocity, false);
   makeInput(this, Vec(68.00, 181.86),  MidiMize::Panel::MeloB_Gate, false);
   makeInput(this, Vec(68.00, 131.07),  MidiMize::Panel::MeloB_Pitch, false);
   makeInput(this, Vec(24.35, 233.16),  MidiMize::Panel::MeloA_Velocity, false);
   makeInput(this, Vec(24.17, 181.86),  MidiMize::Panel::MeloA_Gate, false);
   makeInput(this, Vec(24.17, 131.07),  MidiMize::Panel::MeloA_Pitch, false);

   makeLCD(this, Vec(144.65, 74.42), 2, MidiMize::Panel::Text_MeloD_Channel, 10);
   makeLCD(this, Vec(100.83, 74.42), 2, MidiMize::Panel::Text_MeloC_Channel, 10);
   makeLCD(this, Vec(57.00, 74.42), 2, MidiMize::Panel::Text_MeloB_Channel, 10);
   makeLCD(this, Vec(13.17, 74.42), 2, MidiMize::Panel::Text_MeloA_Channel, 10);
}

#endif // NOT MidiMizeHPP
