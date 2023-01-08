#ifndef MingleHPP
#define MingleHPP

#include "Mingle.h"

#include <SvinOrigin.h>

struct Mingle::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Eight_Start = 0,
      Seven_Start = 1,
      Six_Start = 2,
      Five_Start = 3,
      Four_Start = 4,
      Three_Start = 5,
      Two_Start = 6,
      One_Start = 7,
      // knobs
      // sliders
      Eight_Attenuate = 8,
      Seven_Attenuate = 9,
      Six_Attenuate = 10,
      Five_Attenuate = 11,
      Four_Attenuate = 12,
      Three_Attenuate = 13,
      Two_Attenuate = 14,
      One_Attenuate = 15,
      PARAMS_LEN = 16
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
      Reset = 0,
      Advance = 1,
      Eight_Input = 2,
      Seven_Input = 3,
      Six_Input = 4,
      Five_Input = 5,
      Four_Input = 6,
      Three_Input = 7,
      Two_Input = 8,
      One_Input = 9,
      INPUTS_LEN = 10
   };

   enum OutputId
   {
      Eight_Output = 0,
      Seven_Output = 1,
      Six_Output = 2,
      Five_Output = 3,
      Four_Output = 4,
      Three_Output = 5,
      Two_Output = 6,
      One_Output = 7,
      OUTPUTS_LEN = 8
   };

   enum LightId
   {
      // leds
      RGB_Eight_Current = 0,
      RGB_Seven_Current = 3,
      RGB_Six_Current = 6,
      RGB_Five_Current = 9,
      RGB_Four_Current = 12,
      RGB_Three_Current = 15,
      RGB_Two_Current = 18,
      RGB_One_Current = 21,
      // ledbuttons
      RGB_Eight_Start = 24,
      RGB_Seven_Start = 27,
      RGB_Six_Start = 30,
      RGB_Five_Start = 33,
      RGB_Four_Start = 36,
      RGB_Three_Start = 39,
      RGB_Two_Start = 42,
      RGB_One_Start = 45,
      // sliders
      RGB_Eight_Attenuate = 48,
      RGB_Seven_Attenuate = 51,
      RGB_Six_Attenuate = 54,
      RGB_Five_Attenuate = 57,
      RGB_Four_Attenuate = 60,
      RGB_Three_Attenuate = 63,
      RGB_Two_Attenuate = 66,
      RGB_One_Attenuate = 69,
      LIGHTS_LEN = 72
   };

};

void Mingle::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Eight_Attenuate, 0.0f, 1.0f, 0.0f, "Eight_Attenuate");
   configSwitch(Panel::Seven_Attenuate, 0.0f, 1.0f, 0.0f, "Seven_Attenuate");
   configSwitch(Panel::Six_Attenuate, 0.0f, 1.0f, 0.0f, "Six_Attenuate");
   configSwitch(Panel::Five_Attenuate, 0.0f, 1.0f, 0.0f, "Five_Attenuate");
   configSwitch(Panel::Four_Attenuate, 0.0f, 1.0f, 0.0f, "Four_Attenuate");
   configSwitch(Panel::Three_Attenuate, 0.0f, 1.0f, 0.0f, "Three_Attenuate");
   configSwitch(Panel::Two_Attenuate, 0.0f, 1.0f, 0.0f, "Two_Attenuate");
   configSwitch(Panel::One_Attenuate, 0.0f, 1.0f, 0.0f, "One_Attenuate");

   configButton(Panel::Eight_Start, "Eight_Start");
   configButton(Panel::Seven_Start, "Seven_Start");
   configButton(Panel::Six_Start, "Six_Start");
   configButton(Panel::Five_Start, "Five_Start");
   configButton(Panel::Four_Start, "Four_Start");
   configButton(Panel::Three_Start, "Three_Start");
   configButton(Panel::Two_Start, "Two_Start");
   configButton(Panel::One_Start, "One_Start");

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Advance, "Advance");
   configInput(Panel::Eight_Input, "Eight_Input");
   configInput(Panel::Seven_Input, "Seven_Input");
   configInput(Panel::Six_Input, "Six_Input");
   configInput(Panel::Five_Input, "Five_Input");
   configInput(Panel::Four_Input, "Four_Input");
   configInput(Panel::Three_Input, "Three_Input");
   configInput(Panel::Two_Input, "Two_Input");
   configInput(Panel::One_Input, "One_Input");

   configOutput(Panel::Eight_Output, "Eight_Output");
   configOutput(Panel::Seven_Output, "Seven_Output");
   configOutput(Panel::Six_Output, "Six_Output");
   configOutput(Panel::Five_Output, "Five_Output");
   configOutput(Panel::Four_Output, "Four_Output");
   configOutput(Panel::Three_Output, "Three_Output");
   configOutput(Panel::Two_Output, "Two_Output");
   configOutput(Panel::One_Output, "One_Output");
}

void MingleWidget::setup()
{
   makePanel("res/Utilities/Mingle.svg");

   makeSlider(this, Vec(275.83, 181.36), Mingle::Panel::Eight_Attenuate, Mingle::Panel::RGB_Eight_Attenuate);
   makeSlider(this, Vec(244.16, 181.36), Mingle::Panel::Seven_Attenuate, Mingle::Panel::RGB_Seven_Attenuate);
   makeSlider(this, Vec(212.50, 181.36), Mingle::Panel::Six_Attenuate, Mingle::Panel::RGB_Six_Attenuate);
   makeSlider(this, Vec(180.83, 181.36), Mingle::Panel::Five_Attenuate, Mingle::Panel::RGB_Five_Attenuate);
   makeSlider(this, Vec(149.17, 181.36), Mingle::Panel::Four_Attenuate, Mingle::Panel::RGB_Four_Attenuate);
   makeSlider(this, Vec(117.50, 181.36), Mingle::Panel::Three_Attenuate, Mingle::Panel::RGB_Three_Attenuate);
   makeSlider(this, Vec(85.84, 181.36), Mingle::Panel::Two_Attenuate, Mingle::Panel::RGB_Two_Attenuate);
   makeSlider(this, Vec(54.17, 181.36), Mingle::Panel::One_Attenuate, Mingle::Panel::RGB_One_Attenuate);

   makeLEDButton(this, Vec(275.83, 278.10), Mingle::Panel::Eight_Start, Mingle::Panel::RGB_Eight_Start);
   makeLEDButton(this, Vec(244.16, 278.10), Mingle::Panel::Seven_Start, Mingle::Panel::RGB_Seven_Start);
   makeLEDButton(this, Vec(212.50, 278.10), Mingle::Panel::Six_Start, Mingle::Panel::RGB_Six_Start);
   makeLEDButton(this, Vec(180.83, 278.10), Mingle::Panel::Five_Start, Mingle::Panel::RGB_Five_Start);
   makeLEDButton(this, Vec(149.17, 278.10), Mingle::Panel::Four_Start, Mingle::Panel::RGB_Four_Start);
   makeLEDButton(this, Vec(117.50, 278.10), Mingle::Panel::Three_Start, Mingle::Panel::RGB_Three_Start);
   makeLEDButton(this, Vec(85.84, 278.10), Mingle::Panel::Two_Start, Mingle::Panel::RGB_Two_Start);
   makeLEDButton(this, Vec(54.17, 278.10), Mingle::Panel::One_Start, Mingle::Panel::RGB_One_Start);

   makeInput(this, Vec(64.29, 355.83),  Mingle::Panel::Reset, false);
   makeInput(this, Vec(24.17, 355.83),  Mingle::Panel::Advance, false);
   makeInput(this, Vec(275.83, 244.16),  Mingle::Panel::Eight_Input, false);
   makeInput(this, Vec(244.16, 244.16),  Mingle::Panel::Seven_Input, false);
   makeInput(this, Vec(212.50, 244.16),  Mingle::Panel::Six_Input, false);
   makeInput(this, Vec(180.83, 244.16),  Mingle::Panel::Five_Input, false);
   makeInput(this, Vec(149.17, 244.16),  Mingle::Panel::Four_Input, false);
   makeInput(this, Vec(117.50, 244.16),  Mingle::Panel::Three_Input, false);
   makeInput(this, Vec(85.84, 244.16),  Mingle::Panel::Two_Input, false);
   makeInput(this, Vec(54.17, 244.16),  Mingle::Panel::One_Input, false);

   makeOutput(this, Vec(275.83, 79.40), Mingle::Panel::Eight_Output, false);
   makeOutput(this, Vec(244.16, 79.40), Mingle::Panel::Seven_Output, false);
   makeOutput(this, Vec(212.50, 79.40), Mingle::Panel::Six_Output, false);
   makeOutput(this, Vec(180.83, 79.40), Mingle::Panel::Five_Output, false);
   makeOutput(this, Vec(149.17, 79.40), Mingle::Panel::Four_Output, false);
   makeOutput(this, Vec(117.50, 79.40), Mingle::Panel::Three_Output, false);
   makeOutput(this, Vec(85.84, 79.40), Mingle::Panel::Two_Output, false);
   makeOutput(this, Vec(54.17, 79.40), Mingle::Panel::One_Output, false);

   makeLED(this, Vec(275.83, 108.06), Mingle::Panel::RGB_Eight_Current);
   makeLED(this, Vec(244.16, 108.06), Mingle::Panel::RGB_Seven_Current);
   makeLED(this, Vec(212.50, 108.06), Mingle::Panel::RGB_Six_Current);
   makeLED(this, Vec(180.83, 108.06), Mingle::Panel::RGB_Five_Current);
   makeLED(this, Vec(149.17, 108.06), Mingle::Panel::RGB_Four_Current);
   makeLED(this, Vec(117.50, 108.06), Mingle::Panel::RGB_Three_Current);
   makeLED(this, Vec(85.84, 108.06), Mingle::Panel::RGB_Two_Current);
   makeLED(this, Vec(54.17, 108.06), Mingle::Panel::RGB_One_Current);
}

#endif // NOT MingleHPP
