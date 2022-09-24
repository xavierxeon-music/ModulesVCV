#ifndef SixPackHPP
#define SixPackHPP

#include "SixPack.h"

#include <SvinOrigin.h>

struct SixPack::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      Offset = 0,
      FMAttenuate = 1,
      Six_Detune1_LFO = 2,
      Six_Detune1_Attenuate = 3,
      Six_Detune1_Value = 4,
      Six_Phase1_LFO = 5,
      Six_Phase1_Attenuate = 6,
      Six_Phase1_Value = 7,
      Six_Pan1_LFO = 8,
      Six_Pan1_Attenuate = 9,
      Six_Pan1_Value = 10,
      Five_Detune2_LFO = 11,
      Five_Detune2_Attenuate = 12,
      Five_Detune2_Value = 13,
      Five_Phase2_LFO = 14,
      Five_Phase2_Attenuate = 15,
      Five_Phase2_Value = 16,
      Five_Pan2_LFO = 17,
      Five_Pan2_Attenuate = 18,
      Five_Pan2_Value = 19,
      Four_Detune3_LFO = 20,
      Four_Detune3_Attenuate = 21,
      Four_Detune3_Value = 22,
      Four_Phase3_LFO = 23,
      Four_Phase3_Attenuate = 24,
      Four_Phase3_Value = 25,
      Four_Pan3_LFO = 26,
      Four_Pan3_Attenuate = 27,
      Four_Pan3_Value = 28,
      Three_Detune4_LFO = 29,
      Three_Detune4_Attenuate = 30,
      Three_Detune4_Value = 31,
      Three_Phase4_LFO = 32,
      Three_Phase4_Attenuate = 33,
      Three_Phase4_Value = 34,
      Three_Pan4_LFO = 35,
      Three_Pan4_Attenuate = 36,
      Three_Pan4_Value = 37,
      Two_Detune5_LFO = 38,
      Two_Detune5_Attenuate = 39,
      Two_Detune5_Value = 40,
      Two_Phase5_LFO = 41,
      Two_Phase5_Attenuate = 42,
      Two_Phase5_Value = 43,
      Two_Pan5_LFO = 44,
      Two_Pan5_Attenuate = 45,
      Two_Pan5_Value = 46,
      One_Detune6_LFO = 47,
      One_Detune6_Attenuate = 48,
      One_Detune6_Value = 49,
      One_Phase6_LFO = 50,
      One_Phase6_Attenuate = 51,
      One_Phase6_Value = 52,
      One_Pan6_LFO = 53,
      One_Pan6_Attenuate = 54,
      One_Pan6_Value = 55,
      // sliders
      PARAMS_LEN = 56
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
      Pitch = 0,
      FM = 1,
      Sync = 2,
      Detune_Modulate = 3,
      Phase_Modulate = 4,
      Pan_Modulate = 5,
      INPUTS_LEN = 6
   };

   enum OutputId
   {
      Out = 0,
      One = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      LIGHTS_LEN = 0
   };

};

void SixPack::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configParam(Panel::Offset, -1.f, 1.f, 0.f, "Offset");
   configParam(Panel::FMAttenuate, -1.f, 1.f, 0.f, "FMAttenuate");
   configParam(Panel::Six_Detune1_LFO, -1.f, 1.f, 0.f, "Six_Detune1_LFO");
   configParam(Panel::Six_Detune1_Attenuate, -1.f, 1.f, 0.f, "Six_Detune1_Attenuate");
   configParam(Panel::Six_Detune1_Value, -1.f, 1.f, 0.f, "Six_Detune1_Value");
   configParam(Panel::Six_Phase1_LFO, -1.f, 1.f, 0.f, "Six_Phase1_LFO");
   configParam(Panel::Six_Phase1_Attenuate, -1.f, 1.f, 0.f, "Six_Phase1_Attenuate");
   configParam(Panel::Six_Phase1_Value, -1.f, 1.f, 0.f, "Six_Phase1_Value");
   configParam(Panel::Six_Pan1_LFO, -1.f, 1.f, 0.f, "Six_Pan1_LFO");
   configParam(Panel::Six_Pan1_Attenuate, -1.f, 1.f, 0.f, "Six_Pan1_Attenuate");
   configParam(Panel::Six_Pan1_Value, -1.f, 1.f, 0.f, "Six_Pan1_Value");
   configParam(Panel::Five_Detune2_LFO, -1.f, 1.f, 0.f, "Five_Detune2_LFO");
   configParam(Panel::Five_Detune2_Attenuate, -1.f, 1.f, 0.f, "Five_Detune2_Attenuate");
   configParam(Panel::Five_Detune2_Value, -1.f, 1.f, 0.f, "Five_Detune2_Value");
   configParam(Panel::Five_Phase2_LFO, -1.f, 1.f, 0.f, "Five_Phase2_LFO");
   configParam(Panel::Five_Phase2_Attenuate, -1.f, 1.f, 0.f, "Five_Phase2_Attenuate");
   configParam(Panel::Five_Phase2_Value, -1.f, 1.f, 0.f, "Five_Phase2_Value");
   configParam(Panel::Five_Pan2_LFO, -1.f, 1.f, 0.f, "Five_Pan2_LFO");
   configParam(Panel::Five_Pan2_Attenuate, -1.f, 1.f, 0.f, "Five_Pan2_Attenuate");
   configParam(Panel::Five_Pan2_Value, -1.f, 1.f, 0.f, "Five_Pan2_Value");
   configParam(Panel::Four_Detune3_LFO, -1.f, 1.f, 0.f, "Four_Detune3_LFO");
   configParam(Panel::Four_Detune3_Attenuate, -1.f, 1.f, 0.f, "Four_Detune3_Attenuate");
   configParam(Panel::Four_Detune3_Value, -1.f, 1.f, 0.f, "Four_Detune3_Value");
   configParam(Panel::Four_Phase3_LFO, -1.f, 1.f, 0.f, "Four_Phase3_LFO");
   configParam(Panel::Four_Phase3_Attenuate, -1.f, 1.f, 0.f, "Four_Phase3_Attenuate");
   configParam(Panel::Four_Phase3_Value, -1.f, 1.f, 0.f, "Four_Phase3_Value");
   configParam(Panel::Four_Pan3_LFO, -1.f, 1.f, 0.f, "Four_Pan3_LFO");
   configParam(Panel::Four_Pan3_Attenuate, -1.f, 1.f, 0.f, "Four_Pan3_Attenuate");
   configParam(Panel::Four_Pan3_Value, -1.f, 1.f, 0.f, "Four_Pan3_Value");
   configParam(Panel::Three_Detune4_LFO, -1.f, 1.f, 0.f, "Three_Detune4_LFO");
   configParam(Panel::Three_Detune4_Attenuate, -1.f, 1.f, 0.f, "Three_Detune4_Attenuate");
   configParam(Panel::Three_Detune4_Value, -1.f, 1.f, 0.f, "Three_Detune4_Value");
   configParam(Panel::Three_Phase4_LFO, -1.f, 1.f, 0.f, "Three_Phase4_LFO");
   configParam(Panel::Three_Phase4_Attenuate, -1.f, 1.f, 0.f, "Three_Phase4_Attenuate");
   configParam(Panel::Three_Phase4_Value, -1.f, 1.f, 0.f, "Three_Phase4_Value");
   configParam(Panel::Three_Pan4_LFO, -1.f, 1.f, 0.f, "Three_Pan4_LFO");
   configParam(Panel::Three_Pan4_Attenuate, -1.f, 1.f, 0.f, "Three_Pan4_Attenuate");
   configParam(Panel::Three_Pan4_Value, -1.f, 1.f, 0.f, "Three_Pan4_Value");
   configParam(Panel::Two_Detune5_LFO, -1.f, 1.f, 0.f, "Two_Detune5_LFO");
   configParam(Panel::Two_Detune5_Attenuate, -1.f, 1.f, 0.f, "Two_Detune5_Attenuate");
   configParam(Panel::Two_Detune5_Value, -1.f, 1.f, 0.f, "Two_Detune5_Value");
   configParam(Panel::Two_Phase5_LFO, -1.f, 1.f, 0.f, "Two_Phase5_LFO");
   configParam(Panel::Two_Phase5_Attenuate, -1.f, 1.f, 0.f, "Two_Phase5_Attenuate");
   configParam(Panel::Two_Phase5_Value, -1.f, 1.f, 0.f, "Two_Phase5_Value");
   configParam(Panel::Two_Pan5_LFO, -1.f, 1.f, 0.f, "Two_Pan5_LFO");
   configParam(Panel::Two_Pan5_Attenuate, -1.f, 1.f, 0.f, "Two_Pan5_Attenuate");
   configParam(Panel::Two_Pan5_Value, -1.f, 1.f, 0.f, "Two_Pan5_Value");
   configParam(Panel::One_Detune6_LFO, -1.f, 1.f, 0.f, "One_Detune6_LFO");
   configParam(Panel::One_Detune6_Attenuate, -1.f, 1.f, 0.f, "One_Detune6_Attenuate");
   configParam(Panel::One_Detune6_Value, -1.f, 1.f, 0.f, "One_Detune6_Value");
   configParam(Panel::One_Phase6_LFO, -1.f, 1.f, 0.f, "One_Phase6_LFO");
   configParam(Panel::One_Phase6_Attenuate, -1.f, 1.f, 0.f, "One_Phase6_Attenuate");
   configParam(Panel::One_Phase6_Value, -1.f, 1.f, 0.f, "One_Phase6_Value");
   configParam(Panel::One_Pan6_LFO, -1.f, 1.f, 0.f, "One_Pan6_LFO");
   configParam(Panel::One_Pan6_Attenuate, -1.f, 1.f, 0.f, "One_Pan6_Attenuate");
   configParam(Panel::One_Pan6_Value, -1.f, 1.f, 0.f, "One_Pan6_Value");

   configInput(Panel::Pitch, "Pitch");
   configInput(Panel::FM, "FM");
   configInput(Panel::Sync, "Sync");
   configInput(Panel::Detune_Modulate, "Detune_Modulate");
   configInput(Panel::Phase_Modulate, "Phase_Modulate");
   configInput(Panel::Pan_Modulate, "Pan_Modulate");

   configOutput(Panel::Out, "Out");
   configOutput(Panel::One, "One");
}

void SixPackWidget::setup()
{
   makePanel("res/Synths/SixPack.svg");

   makeKnob(this, Vec(44.36, 344.06), SixPack::Panel::Offset, 4);
   makeKnob(this, Vec(23.43, 227.88), SixPack::Panel::FMAttenuate, 2);
   makeKnob(this, Vec(272.61, 325.40), SixPack::Panel::Six_Detune1_LFO, 1);
   makeKnob(this, Vec(272.61, 295.40), SixPack::Panel::Six_Detune1_Attenuate, 2);
   makeKnob(this, Vec(272.61, 261.03), SixPack::Panel::Six_Detune1_Value, 3);
   makeKnob(this, Vec(272.61, 224.88), SixPack::Panel::Six_Phase1_LFO, 1);
   makeKnob(this, Vec(272.61, 194.88), SixPack::Panel::Six_Phase1_Attenuate, 2);
   makeKnob(this, Vec(272.61, 160.51), SixPack::Panel::Six_Phase1_Value, 3);
   makeKnob(this, Vec(272.61, 124.34), SixPack::Panel::Six_Pan1_LFO, 1);
   makeKnob(this, Vec(272.61, 94.34), SixPack::Panel::Six_Pan1_Attenuate, 2);
   makeKnob(this, Vec(272.61, 59.97), SixPack::Panel::Six_Pan1_Value, 3);
   makeKnob(this, Vec(237.31, 325.40), SixPack::Panel::Five_Detune2_LFO, 1);
   makeKnob(this, Vec(237.31, 295.40), SixPack::Panel::Five_Detune2_Attenuate, 2);
   makeKnob(this, Vec(237.31, 261.03), SixPack::Panel::Five_Detune2_Value, 3);
   makeKnob(this, Vec(237.31, 224.88), SixPack::Panel::Five_Phase2_LFO, 1);
   makeKnob(this, Vec(237.31, 194.88), SixPack::Panel::Five_Phase2_Attenuate, 2);
   makeKnob(this, Vec(237.31, 160.51), SixPack::Panel::Five_Phase2_Value, 3);
   makeKnob(this, Vec(237.31, 124.34), SixPack::Panel::Five_Pan2_LFO, 1);
   makeKnob(this, Vec(237.31, 94.34), SixPack::Panel::Five_Pan2_Attenuate, 2);
   makeKnob(this, Vec(237.31, 59.97), SixPack::Panel::Five_Pan2_Value, 3);
   makeKnob(this, Vec(202.01, 325.40), SixPack::Panel::Four_Detune3_LFO, 1);
   makeKnob(this, Vec(202.01, 295.40), SixPack::Panel::Four_Detune3_Attenuate, 2);
   makeKnob(this, Vec(202.01, 261.03), SixPack::Panel::Four_Detune3_Value, 3);
   makeKnob(this, Vec(202.01, 224.88), SixPack::Panel::Four_Phase3_LFO, 1);
   makeKnob(this, Vec(202.01, 194.88), SixPack::Panel::Four_Phase3_Attenuate, 2);
   makeKnob(this, Vec(202.01, 160.51), SixPack::Panel::Four_Phase3_Value, 3);
   makeKnob(this, Vec(202.01, 124.34), SixPack::Panel::Four_Pan3_LFO, 1);
   makeKnob(this, Vec(202.01, 94.34), SixPack::Panel::Four_Pan3_Attenuate, 2);
   makeKnob(this, Vec(202.01, 59.97), SixPack::Panel::Four_Pan3_Value, 3);
   makeKnob(this, Vec(166.71, 325.40), SixPack::Panel::Three_Detune4_LFO, 1);
   makeKnob(this, Vec(166.71, 295.40), SixPack::Panel::Three_Detune4_Attenuate, 2);
   makeKnob(this, Vec(166.71, 261.03), SixPack::Panel::Three_Detune4_Value, 3);
   makeKnob(this, Vec(166.71, 224.88), SixPack::Panel::Three_Phase4_LFO, 1);
   makeKnob(this, Vec(166.71, 194.88), SixPack::Panel::Three_Phase4_Attenuate, 2);
   makeKnob(this, Vec(166.71, 160.51), SixPack::Panel::Three_Phase4_Value, 3);
   makeKnob(this, Vec(166.71, 124.34), SixPack::Panel::Three_Pan4_LFO, 1);
   makeKnob(this, Vec(166.71, 94.34), SixPack::Panel::Three_Pan4_Attenuate, 2);
   makeKnob(this, Vec(166.71, 59.97), SixPack::Panel::Three_Pan4_Value, 3);
   makeKnob(this, Vec(131.41, 325.40), SixPack::Panel::Two_Detune5_LFO, 1);
   makeKnob(this, Vec(131.41, 295.40), SixPack::Panel::Two_Detune5_Attenuate, 2);
   makeKnob(this, Vec(131.41, 261.03), SixPack::Panel::Two_Detune5_Value, 3);
   makeKnob(this, Vec(131.41, 224.88), SixPack::Panel::Two_Phase5_LFO, 1);
   makeKnob(this, Vec(131.41, 194.88), SixPack::Panel::Two_Phase5_Attenuate, 2);
   makeKnob(this, Vec(131.41, 160.51), SixPack::Panel::Two_Phase5_Value, 3);
   makeKnob(this, Vec(131.41, 124.34), SixPack::Panel::Two_Pan5_LFO, 1);
   makeKnob(this, Vec(131.41, 94.34), SixPack::Panel::Two_Pan5_Attenuate, 2);
   makeKnob(this, Vec(131.41, 59.97), SixPack::Panel::Two_Pan5_Value, 3);
   makeKnob(this, Vec(96.11, 325.40), SixPack::Panel::One_Detune6_LFO, 1);
   makeKnob(this, Vec(96.11, 295.40), SixPack::Panel::One_Detune6_Attenuate, 2);
   makeKnob(this, Vec(96.11, 261.03), SixPack::Panel::One_Detune6_Value, 3);
   makeKnob(this, Vec(96.11, 224.88), SixPack::Panel::One_Phase6_LFO, 1);
   makeKnob(this, Vec(96.11, 194.88), SixPack::Panel::One_Phase6_Attenuate, 2);
   makeKnob(this, Vec(96.11, 160.51), SixPack::Panel::One_Phase6_Value, 3);
   makeKnob(this, Vec(96.11, 124.34), SixPack::Panel::One_Pan6_LFO, 1);
   makeKnob(this, Vec(96.11, 94.34), SixPack::Panel::One_Pan6_Attenuate, 2);
   makeKnob(this, Vec(96.11, 59.97), SixPack::Panel::One_Pan6_Value, 3);

   makeInput(this, Vec(24.17, 294.92),  SixPack::Panel::Pitch, false);
   makeInput(this, Vec(24.17, 194.58),  SixPack::Panel::FM, false);
   makeInput(this, Vec(24.17, 93.29),  SixPack::Panel::Sync, false);
   makeInput(this, Vec(60.75, 294.92),  SixPack::Panel::Detune_Modulate, true);
   makeInput(this, Vec(60.75, 194.40),  SixPack::Panel::Phase_Modulate, true);
   makeInput(this, Vec(60.75, 93.86),  SixPack::Panel::Pan_Modulate, true);

   makeOutput(this, Vec(272.26, 355.83), SixPack::Panel::Out, true);
   makeOutput(this, Vec(166.73, 355.83), SixPack::Panel::One, false);
}

#endif // NOT SixPackHPP
