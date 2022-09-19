#ifndef NosferatuHPP
#define NosferatuHPP

#include "Nosferatu.h"

#include <SvinOrigin.h>

struct Nosferatu::Panel
{
   enum ParamId
   {
      // buttons
      Up = 0,
      Down = 1,
      // switches
      // ledbuttons
      Seg16_Active = 2,
      Seg15_Active = 3,
      Seg14_Active = 4,
      Seg13_Active = 5,
      Seg12_Active = 6,
      Seg11_Active = 7,
      Seg10_Active = 8,
      Seg09_Active = 9,
      Seg08_Active = 10,
      Seg07_Active = 11,
      Seg06_Active = 12,
      Seg05_Active = 13,
      Seg04_Active = 14,
      Seg03_Active = 15,
      Seg02_Active = 16,
      Seg01_Active = 17,
      // knobs
      Seg16_Length = 18,
      Seg15_Length = 19,
      Seg14_Length = 20,
      Seg13_Length = 21,
      Seg12_Length = 22,
      Seg11_Length = 23,
      Seg10_Length = 24,
      Seg09_Length = 25,
      Seg08_Length = 26,
      Seg07_Length = 27,
      Seg06_Length = 28,
      Seg05_Length = 29,
      Seg04_Length = 30,
      Seg03_Length = 31,
      Seg02_Length = 32,
      Seg01_Length = 33,
      // sliders
      Seg16_Ticks = 34,
      Seg16_Pitch = 35,
      Seg15_Ticks = 36,
      Seg15_Pitch = 37,
      Seg14_Ticks = 38,
      Seg14_Pitch = 39,
      Seg13_Ticks = 40,
      Seg13_Pitch = 41,
      Seg12_Ticks = 42,
      Seg12_Pitch = 43,
      Seg11_Ticks = 44,
      Seg11_Pitch = 45,
      Seg10_Ticks = 46,
      Seg10_Pitch = 47,
      Seg09_Ticks = 48,
      Seg09_Pitch = 49,
      Seg08_Ticks = 50,
      Seg08_Pitch = 51,
      Seg07_Ticks = 52,
      Seg07_Pitch = 53,
      Seg06_Ticks = 54,
      Seg06_Pitch = 55,
      Seg05_Ticks = 56,
      Seg05_Pitch = 57,
      Seg04_Ticks = 58,
      Seg04_Pitch = 59,
      Seg03_Ticks = 60,
      Seg03_Pitch = 61,
      Seg02_Ticks = 62,
      Seg02_Pitch = 63,
      Seg01_Ticks = 64,
      Seg01_Pitch = 65,
      PARAMS_LEN = 66
   };

   enum DisplayId
   {
      // lcd
      Text_Bank = 0,
      // oled
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Record = 0,
      BankSelect = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      Pitch = 0,
      Gate = 1,
      First = 2,
      OUTPUTS_LEN = 3
   };

   enum LightId
   {
      // leds
      RGB_Seg16_Current = 0,
      RGB_Seg15_Current = 3,
      RGB_Seg14_Current = 6,
      RGB_Seg13_Current = 9,
      RGB_Seg12_Current = 12,
      RGB_Seg11_Current = 15,
      RGB_Seg10_Current = 18,
      RGB_Seg09_Current = 21,
      RGB_Seg08_Current = 24,
      RGB_Seg07_Current = 27,
      RGB_Seg06_Current = 30,
      RGB_Seg05_Current = 33,
      RGB_Seg04_Current = 36,
      RGB_Seg03_Current = 39,
      RGB_Seg02_Current = 42,
      RGB_Seg01_Current = 45,
      // ledbuttons
      RGB_Seg16_Active = 48,
      RGB_Seg15_Active = 51,
      RGB_Seg14_Active = 54,
      RGB_Seg13_Active = 57,
      RGB_Seg12_Active = 60,
      RGB_Seg11_Active = 63,
      RGB_Seg10_Active = 66,
      RGB_Seg09_Active = 69,
      RGB_Seg08_Active = 72,
      RGB_Seg07_Active = 75,
      RGB_Seg06_Active = 78,
      RGB_Seg05_Active = 81,
      RGB_Seg04_Active = 84,
      RGB_Seg03_Active = 87,
      RGB_Seg02_Active = 90,
      RGB_Seg01_Active = 93,
      // sliders
      RGB_Seg16_Ticks = 96,
      RGB_Seg16_Pitch = 99,
      RGB_Seg15_Ticks = 102,
      RGB_Seg15_Pitch = 105,
      RGB_Seg14_Ticks = 108,
      RGB_Seg14_Pitch = 111,
      RGB_Seg13_Ticks = 114,
      RGB_Seg13_Pitch = 117,
      RGB_Seg12_Ticks = 120,
      RGB_Seg12_Pitch = 123,
      RGB_Seg11_Ticks = 126,
      RGB_Seg11_Pitch = 129,
      RGB_Seg10_Ticks = 132,
      RGB_Seg10_Pitch = 135,
      RGB_Seg09_Ticks = 138,
      RGB_Seg09_Pitch = 141,
      RGB_Seg08_Ticks = 144,
      RGB_Seg08_Pitch = 147,
      RGB_Seg07_Ticks = 150,
      RGB_Seg07_Pitch = 153,
      RGB_Seg06_Ticks = 156,
      RGB_Seg06_Pitch = 159,
      RGB_Seg05_Ticks = 162,
      RGB_Seg05_Pitch = 165,
      RGB_Seg04_Ticks = 168,
      RGB_Seg04_Pitch = 171,
      RGB_Seg03_Ticks = 174,
      RGB_Seg03_Pitch = 177,
      RGB_Seg02_Ticks = 180,
      RGB_Seg02_Pitch = 183,
      RGB_Seg01_Ticks = 186,
      RGB_Seg01_Pitch = 189,
      LIGHTS_LEN = 192
   };

};

void Nosferatu::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Up, "Up");
   configButton(Panel::Down, "Down");

   configSwitch(Panel::Seg16_Ticks, 0.0f, 1.0f, 0.0f, "Seg16_Ticks");
   configSwitch(Panel::Seg16_Pitch, 0.0f, 1.0f, 0.0f, "Seg16_Pitch");
   configSwitch(Panel::Seg15_Ticks, 0.0f, 1.0f, 0.0f, "Seg15_Ticks");
   configSwitch(Panel::Seg15_Pitch, 0.0f, 1.0f, 0.0f, "Seg15_Pitch");
   configSwitch(Panel::Seg14_Ticks, 0.0f, 1.0f, 0.0f, "Seg14_Ticks");
   configSwitch(Panel::Seg14_Pitch, 0.0f, 1.0f, 0.0f, "Seg14_Pitch");
   configSwitch(Panel::Seg13_Ticks, 0.0f, 1.0f, 0.0f, "Seg13_Ticks");
   configSwitch(Panel::Seg13_Pitch, 0.0f, 1.0f, 0.0f, "Seg13_Pitch");
   configSwitch(Panel::Seg12_Ticks, 0.0f, 1.0f, 0.0f, "Seg12_Ticks");
   configSwitch(Panel::Seg12_Pitch, 0.0f, 1.0f, 0.0f, "Seg12_Pitch");
   configSwitch(Panel::Seg11_Ticks, 0.0f, 1.0f, 0.0f, "Seg11_Ticks");
   configSwitch(Panel::Seg11_Pitch, 0.0f, 1.0f, 0.0f, "Seg11_Pitch");
   configSwitch(Panel::Seg10_Ticks, 0.0f, 1.0f, 0.0f, "Seg10_Ticks");
   configSwitch(Panel::Seg10_Pitch, 0.0f, 1.0f, 0.0f, "Seg10_Pitch");
   configSwitch(Panel::Seg09_Ticks, 0.0f, 1.0f, 0.0f, "Seg09_Ticks");
   configSwitch(Panel::Seg09_Pitch, 0.0f, 1.0f, 0.0f, "Seg09_Pitch");
   configSwitch(Panel::Seg08_Ticks, 0.0f, 1.0f, 0.0f, "Seg08_Ticks");
   configSwitch(Panel::Seg08_Pitch, 0.0f, 1.0f, 0.0f, "Seg08_Pitch");
   configSwitch(Panel::Seg07_Ticks, 0.0f, 1.0f, 0.0f, "Seg07_Ticks");
   configSwitch(Panel::Seg07_Pitch, 0.0f, 1.0f, 0.0f, "Seg07_Pitch");
   configSwitch(Panel::Seg06_Ticks, 0.0f, 1.0f, 0.0f, "Seg06_Ticks");
   configSwitch(Panel::Seg06_Pitch, 0.0f, 1.0f, 0.0f, "Seg06_Pitch");
   configSwitch(Panel::Seg05_Ticks, 0.0f, 1.0f, 0.0f, "Seg05_Ticks");
   configSwitch(Panel::Seg05_Pitch, 0.0f, 1.0f, 0.0f, "Seg05_Pitch");
   configSwitch(Panel::Seg04_Ticks, 0.0f, 1.0f, 0.0f, "Seg04_Ticks");
   configSwitch(Panel::Seg04_Pitch, 0.0f, 1.0f, 0.0f, "Seg04_Pitch");
   configSwitch(Panel::Seg03_Ticks, 0.0f, 1.0f, 0.0f, "Seg03_Ticks");
   configSwitch(Panel::Seg03_Pitch, 0.0f, 1.0f, 0.0f, "Seg03_Pitch");
   configSwitch(Panel::Seg02_Ticks, 0.0f, 1.0f, 0.0f, "Seg02_Ticks");
   configSwitch(Panel::Seg02_Pitch, 0.0f, 1.0f, 0.0f, "Seg02_Pitch");
   configSwitch(Panel::Seg01_Ticks, 0.0f, 1.0f, 0.0f, "Seg01_Ticks");
   configSwitch(Panel::Seg01_Pitch, 0.0f, 1.0f, 0.0f, "Seg01_Pitch");

   configButton(Panel::Seg16_Active, "Seg16_Active");
   configButton(Panel::Seg15_Active, "Seg15_Active");
   configButton(Panel::Seg14_Active, "Seg14_Active");
   configButton(Panel::Seg13_Active, "Seg13_Active");
   configButton(Panel::Seg12_Active, "Seg12_Active");
   configButton(Panel::Seg11_Active, "Seg11_Active");
   configButton(Panel::Seg10_Active, "Seg10_Active");
   configButton(Panel::Seg09_Active, "Seg09_Active");
   configButton(Panel::Seg08_Active, "Seg08_Active");
   configButton(Panel::Seg07_Active, "Seg07_Active");
   configButton(Panel::Seg06_Active, "Seg06_Active");
   configButton(Panel::Seg05_Active, "Seg05_Active");
   configButton(Panel::Seg04_Active, "Seg04_Active");
   configButton(Panel::Seg03_Active, "Seg03_Active");
   configButton(Panel::Seg02_Active, "Seg02_Active");
   configButton(Panel::Seg01_Active, "Seg01_Active");

   configParam(Panel::Seg16_Length, -1.f, 1.f, 0.f, "Seg16_Length");
   configParam(Panel::Seg15_Length, -1.f, 1.f, 0.f, "Seg15_Length");
   configParam(Panel::Seg14_Length, -1.f, 1.f, 0.f, "Seg14_Length");
   configParam(Panel::Seg13_Length, -1.f, 1.f, 0.f, "Seg13_Length");
   configParam(Panel::Seg12_Length, -1.f, 1.f, 0.f, "Seg12_Length");
   configParam(Panel::Seg11_Length, -1.f, 1.f, 0.f, "Seg11_Length");
   configParam(Panel::Seg10_Length, -1.f, 1.f, 0.f, "Seg10_Length");
   configParam(Panel::Seg09_Length, -1.f, 1.f, 0.f, "Seg09_Length");
   configParam(Panel::Seg08_Length, -1.f, 1.f, 0.f, "Seg08_Length");
   configParam(Panel::Seg07_Length, -1.f, 1.f, 0.f, "Seg07_Length");
   configParam(Panel::Seg06_Length, -1.f, 1.f, 0.f, "Seg06_Length");
   configParam(Panel::Seg05_Length, -1.f, 1.f, 0.f, "Seg05_Length");
   configParam(Panel::Seg04_Length, -1.f, 1.f, 0.f, "Seg04_Length");
   configParam(Panel::Seg03_Length, -1.f, 1.f, 0.f, "Seg03_Length");
   configParam(Panel::Seg02_Length, -1.f, 1.f, 0.f, "Seg02_Length");
   configParam(Panel::Seg01_Length, -1.f, 1.f, 0.f, "Seg01_Length");

   configInput(Panel::Record, "Record");
   configInput(Panel::BankSelect, "BankSelect");

   configOutput(Panel::Pitch, "Pitch");
   configOutput(Panel::Gate, "Gate");
   configOutput(Panel::First, "First");
}

void NosferatuWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Sequencer/Nosferatu.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(138.38, 355.83), Nosferatu::Panel::Up);
   makeButton(this, Vec(76.95, 355.83), Nosferatu::Panel::Down);

   makeSlider(this, Vec(431.08, 204.67), Nosferatu::Panel::Seg16_Ticks, Nosferatu::Panel::RGB_Seg16_Ticks);
   makeSlider(this, Vec(431.08, 113.05), Nosferatu::Panel::Seg16_Pitch, Nosferatu::Panel::RGB_Seg16_Pitch);
   makeSlider(this, Vec(405.29, 204.67), Nosferatu::Panel::Seg15_Ticks, Nosferatu::Panel::RGB_Seg15_Ticks);
   makeSlider(this, Vec(405.29, 113.05), Nosferatu::Panel::Seg15_Pitch, Nosferatu::Panel::RGB_Seg15_Pitch);
   makeSlider(this, Vec(379.51, 204.67), Nosferatu::Panel::Seg14_Ticks, Nosferatu::Panel::RGB_Seg14_Ticks);
   makeSlider(this, Vec(379.51, 113.05), Nosferatu::Panel::Seg14_Pitch, Nosferatu::Panel::RGB_Seg14_Pitch);
   makeSlider(this, Vec(353.72, 204.67), Nosferatu::Panel::Seg13_Ticks, Nosferatu::Panel::RGB_Seg13_Ticks);
   makeSlider(this, Vec(353.72, 113.05), Nosferatu::Panel::Seg13_Pitch, Nosferatu::Panel::RGB_Seg13_Pitch);
   makeSlider(this, Vec(327.93, 204.67), Nosferatu::Panel::Seg12_Ticks, Nosferatu::Panel::RGB_Seg12_Ticks);
   makeSlider(this, Vec(327.93, 113.05), Nosferatu::Panel::Seg12_Pitch, Nosferatu::Panel::RGB_Seg12_Pitch);
   makeSlider(this, Vec(302.15, 204.67), Nosferatu::Panel::Seg11_Ticks, Nosferatu::Panel::RGB_Seg11_Ticks);
   makeSlider(this, Vec(302.15, 113.05), Nosferatu::Panel::Seg11_Pitch, Nosferatu::Panel::RGB_Seg11_Pitch);
   makeSlider(this, Vec(276.36, 204.67), Nosferatu::Panel::Seg10_Ticks, Nosferatu::Panel::RGB_Seg10_Ticks);
   makeSlider(this, Vec(276.36, 113.05), Nosferatu::Panel::Seg10_Pitch, Nosferatu::Panel::RGB_Seg10_Pitch);
   makeSlider(this, Vec(250.57, 204.67), Nosferatu::Panel::Seg09_Ticks, Nosferatu::Panel::RGB_Seg09_Ticks);
   makeSlider(this, Vec(250.57, 113.05), Nosferatu::Panel::Seg09_Pitch, Nosferatu::Panel::RGB_Seg09_Pitch);
   makeSlider(this, Vec(224.79, 204.45), Nosferatu::Panel::Seg08_Ticks, Nosferatu::Panel::RGB_Seg08_Ticks);
   makeSlider(this, Vec(224.79, 112.82), Nosferatu::Panel::Seg08_Pitch, Nosferatu::Panel::RGB_Seg08_Pitch);
   makeSlider(this, Vec(199.00, 204.45), Nosferatu::Panel::Seg07_Ticks, Nosferatu::Panel::RGB_Seg07_Ticks);
   makeSlider(this, Vec(199.00, 112.82), Nosferatu::Panel::Seg07_Pitch, Nosferatu::Panel::RGB_Seg07_Pitch);
   makeSlider(this, Vec(173.22, 204.45), Nosferatu::Panel::Seg06_Ticks, Nosferatu::Panel::RGB_Seg06_Ticks);
   makeSlider(this, Vec(173.22, 112.82), Nosferatu::Panel::Seg06_Pitch, Nosferatu::Panel::RGB_Seg06_Pitch);
   makeSlider(this, Vec(147.43, 204.45), Nosferatu::Panel::Seg05_Ticks, Nosferatu::Panel::RGB_Seg05_Ticks);
   makeSlider(this, Vec(147.43, 112.82), Nosferatu::Panel::Seg05_Pitch, Nosferatu::Panel::RGB_Seg05_Pitch);
   makeSlider(this, Vec(121.64, 204.45), Nosferatu::Panel::Seg04_Ticks, Nosferatu::Panel::RGB_Seg04_Ticks);
   makeSlider(this, Vec(121.64, 112.82), Nosferatu::Panel::Seg04_Pitch, Nosferatu::Panel::RGB_Seg04_Pitch);
   makeSlider(this, Vec(95.86, 204.45), Nosferatu::Panel::Seg03_Ticks, Nosferatu::Panel::RGB_Seg03_Ticks);
   makeSlider(this, Vec(95.86, 112.82), Nosferatu::Panel::Seg03_Pitch, Nosferatu::Panel::RGB_Seg03_Pitch);
   makeSlider(this, Vec(70.07, 204.45), Nosferatu::Panel::Seg02_Ticks, Nosferatu::Panel::RGB_Seg02_Ticks);
   makeSlider(this, Vec(70.07, 112.82), Nosferatu::Panel::Seg02_Pitch, Nosferatu::Panel::RGB_Seg02_Pitch);
   makeSlider(this, Vec(44.28, 204.45), Nosferatu::Panel::Seg01_Ticks, Nosferatu::Panel::RGB_Seg01_Ticks);
   makeSlider(this, Vec(44.28, 112.82), Nosferatu::Panel::Seg01_Pitch, Nosferatu::Panel::RGB_Seg01_Pitch);

   makeLEDButton(this, Vec(431.08, 310.17), Nosferatu::Panel::Seg16_Active, Nosferatu::Panel::RGB_Seg16_Active);
   makeLEDButton(this, Vec(405.29, 310.17), Nosferatu::Panel::Seg15_Active, Nosferatu::Panel::RGB_Seg15_Active);
   makeLEDButton(this, Vec(379.51, 310.17), Nosferatu::Panel::Seg14_Active, Nosferatu::Panel::RGB_Seg14_Active);
   makeLEDButton(this, Vec(353.72, 310.17), Nosferatu::Panel::Seg13_Active, Nosferatu::Panel::RGB_Seg13_Active);
   makeLEDButton(this, Vec(327.93, 310.17), Nosferatu::Panel::Seg12_Active, Nosferatu::Panel::RGB_Seg12_Active);
   makeLEDButton(this, Vec(302.15, 310.17), Nosferatu::Panel::Seg11_Active, Nosferatu::Panel::RGB_Seg11_Active);
   makeLEDButton(this, Vec(276.36, 310.17), Nosferatu::Panel::Seg10_Active, Nosferatu::Panel::RGB_Seg10_Active);
   makeLEDButton(this, Vec(250.57, 310.17), Nosferatu::Panel::Seg09_Active, Nosferatu::Panel::RGB_Seg09_Active);
   makeLEDButton(this, Vec(224.79, 309.94), Nosferatu::Panel::Seg08_Active, Nosferatu::Panel::RGB_Seg08_Active);
   makeLEDButton(this, Vec(199.00, 309.94), Nosferatu::Panel::Seg07_Active, Nosferatu::Panel::RGB_Seg07_Active);
   makeLEDButton(this, Vec(173.22, 309.94), Nosferatu::Panel::Seg06_Active, Nosferatu::Panel::RGB_Seg06_Active);
   makeLEDButton(this, Vec(147.43, 309.94), Nosferatu::Panel::Seg05_Active, Nosferatu::Panel::RGB_Seg05_Active);
   makeLEDButton(this, Vec(121.64, 309.94), Nosferatu::Panel::Seg04_Active, Nosferatu::Panel::RGB_Seg04_Active);
   makeLEDButton(this, Vec(95.86, 309.94), Nosferatu::Panel::Seg03_Active, Nosferatu::Panel::RGB_Seg03_Active);
   makeLEDButton(this, Vec(70.07, 309.94), Nosferatu::Panel::Seg02_Active, Nosferatu::Panel::RGB_Seg02_Active);
   makeLEDButton(this, Vec(44.28, 309.94), Nosferatu::Panel::Seg01_Active, Nosferatu::Panel::RGB_Seg01_Active);

   makeKnob(this, Vec(430.41, 282.57), Nosferatu::Panel::Seg16_Length, 2);
   makeKnob(this, Vec(404.62, 265.57), Nosferatu::Panel::Seg15_Length, 2);
   makeKnob(this, Vec(378.83, 282.57), Nosferatu::Panel::Seg14_Length, 2);
   makeKnob(this, Vec(353.05, 265.57), Nosferatu::Panel::Seg13_Length, 2);
   makeKnob(this, Vec(327.26, 282.57), Nosferatu::Panel::Seg12_Length, 2);
   makeKnob(this, Vec(301.47, 265.57), Nosferatu::Panel::Seg11_Length, 2);
   makeKnob(this, Vec(275.69, 282.57), Nosferatu::Panel::Seg10_Length, 2);
   makeKnob(this, Vec(249.90, 265.57), Nosferatu::Panel::Seg09_Length, 2);
   makeKnob(this, Vec(224.12, 282.34), Nosferatu::Panel::Seg08_Length, 2);
   makeKnob(this, Vec(198.33, 265.34), Nosferatu::Panel::Seg07_Length, 2);
   makeKnob(this, Vec(172.54, 282.34), Nosferatu::Panel::Seg06_Length, 2);
   makeKnob(this, Vec(146.76, 265.34), Nosferatu::Panel::Seg05_Length, 2);
   makeKnob(this, Vec(120.97, 282.34), Nosferatu::Panel::Seg04_Length, 2);
   makeKnob(this, Vec(95.18, 265.34), Nosferatu::Panel::Seg03_Length, 2);
   makeKnob(this, Vec(69.40, 282.34), Nosferatu::Panel::Seg02_Length, 2);
   makeKnob(this, Vec(43.61, 265.34), Nosferatu::Panel::Seg01_Length, 2);

   makeInput(this, Vec(210.83, 355.83),  Nosferatu::Panel::Record, false);
   makeInput(this, Vec(44.99, 355.83),  Nosferatu::Panel::BankSelect, false);

   makeOutput(this, Vec(425.83, 355.83), Nosferatu::Panel::Pitch, false);
   makeOutput(this, Vec(373.40, 355.83), Nosferatu::Panel::Gate, false);
   makeOutput(this, Vec(293.88, 355.83), Nosferatu::Panel::First, false);

   makeLED(this, Vec(431.08, 62.75), Nosferatu::Panel::RGB_Seg16_Current);
   makeLED(this, Vec(405.29, 62.75), Nosferatu::Panel::RGB_Seg15_Current);
   makeLED(this, Vec(379.51, 62.75), Nosferatu::Panel::RGB_Seg14_Current);
   makeLED(this, Vec(353.72, 62.75), Nosferatu::Panel::RGB_Seg13_Current);
   makeLED(this, Vec(327.93, 62.75), Nosferatu::Panel::RGB_Seg12_Current);
   makeLED(this, Vec(302.15, 62.75), Nosferatu::Panel::RGB_Seg11_Current);
   makeLED(this, Vec(276.36, 62.75), Nosferatu::Panel::RGB_Seg10_Current);
   makeLED(this, Vec(250.57, 62.75), Nosferatu::Panel::RGB_Seg09_Current);
   makeLED(this, Vec(224.79, 62.52), Nosferatu::Panel::RGB_Seg08_Current);
   makeLED(this, Vec(199.00, 62.52), Nosferatu::Panel::RGB_Seg07_Current);
   makeLED(this, Vec(173.22, 62.52), Nosferatu::Panel::RGB_Seg06_Current);
   makeLED(this, Vec(147.43, 62.52), Nosferatu::Panel::RGB_Seg05_Current);
   makeLED(this, Vec(121.64, 62.52), Nosferatu::Panel::RGB_Seg04_Current);
   makeLED(this, Vec(95.86, 62.52), Nosferatu::Panel::RGB_Seg03_Current);
   makeLED(this, Vec(70.07, 62.52), Nosferatu::Panel::RGB_Seg02_Current);
   makeLED(this, Vec(44.28, 62.52), Nosferatu::Panel::RGB_Seg01_Current);

   makeLCD(this, Vec(90.04, 343.83), 2, Nosferatu::Panel::Text_Bank, 18);
}

#endif // NOT NosferatuHPP
