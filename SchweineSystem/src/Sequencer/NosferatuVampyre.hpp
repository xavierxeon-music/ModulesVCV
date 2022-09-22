#ifndef NosferatuVampyreHPP
#define NosferatuVampyreHPP

#include "NosferatuVampyre.h"

#include <SvinOrigin.h>

namespace Nosferatu
{
   struct Vampyre::Panel
   {
      enum ParamId
      {
         // buttons
         Down = 0,
         Up = 1,
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
         Seg16_Chance = 19,
         Seg15_Length = 20,
         Seg15_Chance = 21,
         Seg14_Length = 22,
         Seg14_Chance = 23,
         Seg13_Length = 24,
         Seg13_Chance = 25,
         Seg12_Length = 26,
         Seg12_Chance = 27,
         Seg11_Length = 28,
         Seg11_Chance = 29,
         Seg10_Length = 30,
         Seg10_Chance = 31,
         Seg09_Length = 32,
         Seg09_Chance = 33,
         Seg08_Length = 34,
         Seg08_Chance = 35,
         Seg07_Length = 36,
         Seg07_Chance = 37,
         Seg06_Length = 38,
         Seg06_Chance = 39,
         Seg05_Length = 40,
         Seg05_Chance = 41,
         Seg04_Length = 42,
         Seg04_Chance = 43,
         Seg03_Length = 44,
         Seg03_Chance = 45,
         Seg02_Length = 46,
         Seg02_Chance = 47,
         Seg01_Length = 48,
         Seg01_Chance = 49,
         Offset = 50,
         // sliders
         Seg16_Ticks = 51,
         Seg16_Pitch = 52,
         Seg15_Ticks = 53,
         Seg15_Pitch = 54,
         Seg14_Ticks = 55,
         Seg14_Pitch = 56,
         Seg13_Ticks = 57,
         Seg13_Pitch = 58,
         Seg12_Ticks = 59,
         Seg12_Pitch = 60,
         Seg11_Ticks = 61,
         Seg11_Pitch = 62,
         Seg10_Ticks = 63,
         Seg10_Pitch = 64,
         Seg09_Ticks = 65,
         Seg09_Pitch = 66,
         Seg08_Ticks = 67,
         Seg08_Pitch = 68,
         Seg07_Ticks = 69,
         Seg07_Pitch = 70,
         Seg06_Ticks = 71,
         Seg06_Pitch = 72,
         Seg05_Ticks = 73,
         Seg05_Pitch = 74,
         Seg04_Ticks = 75,
         Seg04_Pitch = 76,
         Seg03_Ticks = 77,
         Seg03_Pitch = 78,
         Seg02_Ticks = 79,
         Seg02_Pitch = 80,
         Seg01_Ticks = 81,
         Seg01_Pitch = 82,
         PARAMS_LEN = 83
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
         BankSelect = 0,
         INPUTS_LEN = 1
      };

      enum OutputId
      {
         Gate = 0,
         Pitch = 1,
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

   void Vampyre::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

      configButton(Panel::Down, "Down");
      configButton(Panel::Up, "Up");

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
      configParam(Panel::Seg16_Chance, -1.f, 1.f, 0.f, "Seg16_Chance");
      configParam(Panel::Seg15_Length, -1.f, 1.f, 0.f, "Seg15_Length");
      configParam(Panel::Seg15_Chance, -1.f, 1.f, 0.f, "Seg15_Chance");
      configParam(Panel::Seg14_Length, -1.f, 1.f, 0.f, "Seg14_Length");
      configParam(Panel::Seg14_Chance, -1.f, 1.f, 0.f, "Seg14_Chance");
      configParam(Panel::Seg13_Length, -1.f, 1.f, 0.f, "Seg13_Length");
      configParam(Panel::Seg13_Chance, -1.f, 1.f, 0.f, "Seg13_Chance");
      configParam(Panel::Seg12_Length, -1.f, 1.f, 0.f, "Seg12_Length");
      configParam(Panel::Seg12_Chance, -1.f, 1.f, 0.f, "Seg12_Chance");
      configParam(Panel::Seg11_Length, -1.f, 1.f, 0.f, "Seg11_Length");
      configParam(Panel::Seg11_Chance, -1.f, 1.f, 0.f, "Seg11_Chance");
      configParam(Panel::Seg10_Length, -1.f, 1.f, 0.f, "Seg10_Length");
      configParam(Panel::Seg10_Chance, -1.f, 1.f, 0.f, "Seg10_Chance");
      configParam(Panel::Seg09_Length, -1.f, 1.f, 0.f, "Seg09_Length");
      configParam(Panel::Seg09_Chance, -1.f, 1.f, 0.f, "Seg09_Chance");
      configParam(Panel::Seg08_Length, -1.f, 1.f, 0.f, "Seg08_Length");
      configParam(Panel::Seg08_Chance, -1.f, 1.f, 0.f, "Seg08_Chance");
      configParam(Panel::Seg07_Length, -1.f, 1.f, 0.f, "Seg07_Length");
      configParam(Panel::Seg07_Chance, -1.f, 1.f, 0.f, "Seg07_Chance");
      configParam(Panel::Seg06_Length, -1.f, 1.f, 0.f, "Seg06_Length");
      configParam(Panel::Seg06_Chance, -1.f, 1.f, 0.f, "Seg06_Chance");
      configParam(Panel::Seg05_Length, -1.f, 1.f, 0.f, "Seg05_Length");
      configParam(Panel::Seg05_Chance, -1.f, 1.f, 0.f, "Seg05_Chance");
      configParam(Panel::Seg04_Length, -1.f, 1.f, 0.f, "Seg04_Length");
      configParam(Panel::Seg04_Chance, -1.f, 1.f, 0.f, "Seg04_Chance");
      configParam(Panel::Seg03_Length, -1.f, 1.f, 0.f, "Seg03_Length");
      configParam(Panel::Seg03_Chance, -1.f, 1.f, 0.f, "Seg03_Chance");
      configParam(Panel::Seg02_Length, -1.f, 1.f, 0.f, "Seg02_Length");
      configParam(Panel::Seg02_Chance, -1.f, 1.f, 0.f, "Seg02_Chance");
      configParam(Panel::Seg01_Length, -1.f, 1.f, 0.f, "Seg01_Length");
      configParam(Panel::Seg01_Chance, -1.f, 1.f, 0.f, "Seg01_Chance");
      configParam(Panel::Offset, -1.f, 1.f, 0.f, "Offset");

      configInput(Panel::BankSelect, "BankSelect");

      configOutput(Panel::Gate, "Gate");
      configOutput(Panel::Pitch, "Pitch");
      configOutput(Panel::First, "First");
   }

   void VampyreWidget::setup()
   {
      std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Sequencer/NosferatuVampyre.svg");
      SvgPanel* mainPanel = createPanel(panelPath);
      setPanel(mainPanel);

      makeButton(this, Vec(35.00, 197.46), Vampyre::Panel::Down);
      makeButton(this, Vec(35.00, 179.98), Vampyre::Panel::Up);

      makeSlider(this, Vec(490.08, 235.67), Vampyre::Panel::Seg16_Ticks, Vampyre::Panel::RGB_Seg16_Ticks);
      makeSlider(this, Vec(490.08, 144.05), Vampyre::Panel::Seg16_Pitch, Vampyre::Panel::RGB_Seg16_Pitch);
      makeSlider(this, Vec(464.29, 235.67), Vampyre::Panel::Seg15_Ticks, Vampyre::Panel::RGB_Seg15_Ticks);
      makeSlider(this, Vec(464.29, 144.05), Vampyre::Panel::Seg15_Pitch, Vampyre::Panel::RGB_Seg15_Pitch);
      makeSlider(this, Vec(438.51, 235.67), Vampyre::Panel::Seg14_Ticks, Vampyre::Panel::RGB_Seg14_Ticks);
      makeSlider(this, Vec(438.51, 144.05), Vampyre::Panel::Seg14_Pitch, Vampyre::Panel::RGB_Seg14_Pitch);
      makeSlider(this, Vec(412.72, 235.67), Vampyre::Panel::Seg13_Ticks, Vampyre::Panel::RGB_Seg13_Ticks);
      makeSlider(this, Vec(412.72, 144.05), Vampyre::Panel::Seg13_Pitch, Vampyre::Panel::RGB_Seg13_Pitch);
      makeSlider(this, Vec(386.93, 235.67), Vampyre::Panel::Seg12_Ticks, Vampyre::Panel::RGB_Seg12_Ticks);
      makeSlider(this, Vec(386.93, 144.05), Vampyre::Panel::Seg12_Pitch, Vampyre::Panel::RGB_Seg12_Pitch);
      makeSlider(this, Vec(361.15, 235.67), Vampyre::Panel::Seg11_Ticks, Vampyre::Panel::RGB_Seg11_Ticks);
      makeSlider(this, Vec(361.15, 144.05), Vampyre::Panel::Seg11_Pitch, Vampyre::Panel::RGB_Seg11_Pitch);
      makeSlider(this, Vec(335.36, 235.67), Vampyre::Panel::Seg10_Ticks, Vampyre::Panel::RGB_Seg10_Ticks);
      makeSlider(this, Vec(335.36, 144.05), Vampyre::Panel::Seg10_Pitch, Vampyre::Panel::RGB_Seg10_Pitch);
      makeSlider(this, Vec(309.57, 235.67), Vampyre::Panel::Seg09_Ticks, Vampyre::Panel::RGB_Seg09_Ticks);
      makeSlider(this, Vec(309.57, 144.05), Vampyre::Panel::Seg09_Pitch, Vampyre::Panel::RGB_Seg09_Pitch);
      makeSlider(this, Vec(283.79, 235.45), Vampyre::Panel::Seg08_Ticks, Vampyre::Panel::RGB_Seg08_Ticks);
      makeSlider(this, Vec(283.79, 143.82), Vampyre::Panel::Seg08_Pitch, Vampyre::Panel::RGB_Seg08_Pitch);
      makeSlider(this, Vec(258.00, 235.45), Vampyre::Panel::Seg07_Ticks, Vampyre::Panel::RGB_Seg07_Ticks);
      makeSlider(this, Vec(258.00, 143.82), Vampyre::Panel::Seg07_Pitch, Vampyre::Panel::RGB_Seg07_Pitch);
      makeSlider(this, Vec(232.22, 235.45), Vampyre::Panel::Seg06_Ticks, Vampyre::Panel::RGB_Seg06_Ticks);
      makeSlider(this, Vec(232.22, 143.82), Vampyre::Panel::Seg06_Pitch, Vampyre::Panel::RGB_Seg06_Pitch);
      makeSlider(this, Vec(206.43, 235.45), Vampyre::Panel::Seg05_Ticks, Vampyre::Panel::RGB_Seg05_Ticks);
      makeSlider(this, Vec(206.43, 143.82), Vampyre::Panel::Seg05_Pitch, Vampyre::Panel::RGB_Seg05_Pitch);
      makeSlider(this, Vec(180.64, 235.45), Vampyre::Panel::Seg04_Ticks, Vampyre::Panel::RGB_Seg04_Ticks);
      makeSlider(this, Vec(180.64, 143.82), Vampyre::Panel::Seg04_Pitch, Vampyre::Panel::RGB_Seg04_Pitch);
      makeSlider(this, Vec(154.86, 235.45), Vampyre::Panel::Seg03_Ticks, Vampyre::Panel::RGB_Seg03_Ticks);
      makeSlider(this, Vec(154.86, 143.82), Vampyre::Panel::Seg03_Pitch, Vampyre::Panel::RGB_Seg03_Pitch);
      makeSlider(this, Vec(129.07, 235.45), Vampyre::Panel::Seg02_Ticks, Vampyre::Panel::RGB_Seg02_Ticks);
      makeSlider(this, Vec(129.07, 143.82), Vampyre::Panel::Seg02_Pitch, Vampyre::Panel::RGB_Seg02_Pitch);
      makeSlider(this, Vec(103.28, 235.45), Vampyre::Panel::Seg01_Ticks, Vampyre::Panel::RGB_Seg01_Ticks);
      makeSlider(this, Vec(103.28, 143.82), Vampyre::Panel::Seg01_Pitch, Vampyre::Panel::RGB_Seg01_Pitch);

      makeLEDButton(this, Vec(490.08, 344.17), Vampyre::Panel::Seg16_Active, Vampyre::Panel::RGB_Seg16_Active);
      makeLEDButton(this, Vec(464.29, 344.17), Vampyre::Panel::Seg15_Active, Vampyre::Panel::RGB_Seg15_Active);
      makeLEDButton(this, Vec(438.51, 344.17), Vampyre::Panel::Seg14_Active, Vampyre::Panel::RGB_Seg14_Active);
      makeLEDButton(this, Vec(412.72, 344.17), Vampyre::Panel::Seg13_Active, Vampyre::Panel::RGB_Seg13_Active);
      makeLEDButton(this, Vec(386.93, 344.17), Vampyre::Panel::Seg12_Active, Vampyre::Panel::RGB_Seg12_Active);
      makeLEDButton(this, Vec(361.15, 344.17), Vampyre::Panel::Seg11_Active, Vampyre::Panel::RGB_Seg11_Active);
      makeLEDButton(this, Vec(335.36, 344.17), Vampyre::Panel::Seg10_Active, Vampyre::Panel::RGB_Seg10_Active);
      makeLEDButton(this, Vec(309.57, 344.17), Vampyre::Panel::Seg09_Active, Vampyre::Panel::RGB_Seg09_Active);
      makeLEDButton(this, Vec(283.79, 343.94), Vampyre::Panel::Seg08_Active, Vampyre::Panel::RGB_Seg08_Active);
      makeLEDButton(this, Vec(258.00, 343.94), Vampyre::Panel::Seg07_Active, Vampyre::Panel::RGB_Seg07_Active);
      makeLEDButton(this, Vec(232.22, 343.94), Vampyre::Panel::Seg06_Active, Vampyre::Panel::RGB_Seg06_Active);
      makeLEDButton(this, Vec(206.43, 343.94), Vampyre::Panel::Seg05_Active, Vampyre::Panel::RGB_Seg05_Active);
      makeLEDButton(this, Vec(180.64, 343.94), Vampyre::Panel::Seg04_Active, Vampyre::Panel::RGB_Seg04_Active);
      makeLEDButton(this, Vec(154.86, 343.94), Vampyre::Panel::Seg03_Active, Vampyre::Panel::RGB_Seg03_Active);
      makeLEDButton(this, Vec(129.07, 343.94), Vampyre::Panel::Seg02_Active, Vampyre::Panel::RGB_Seg02_Active);
      makeLEDButton(this, Vec(103.28, 343.94), Vampyre::Panel::Seg01_Active, Vampyre::Panel::RGB_Seg01_Active);

      makeKnob(this, Vec(489.41, 313.57), Vampyre::Panel::Seg16_Length, 2);
      makeKnob(this, Vec(489.41, 91.57), Vampyre::Panel::Seg16_Chance, 1);
      makeKnob(this, Vec(463.62, 296.57), Vampyre::Panel::Seg15_Length, 2);
      makeKnob(this, Vec(463.62, 74.57), Vampyre::Panel::Seg15_Chance, 1);
      makeKnob(this, Vec(437.83, 313.57), Vampyre::Panel::Seg14_Length, 2);
      makeKnob(this, Vec(437.83, 91.57), Vampyre::Panel::Seg14_Chance, 1);
      makeKnob(this, Vec(412.05, 296.57), Vampyre::Panel::Seg13_Length, 2);
      makeKnob(this, Vec(412.05, 74.57), Vampyre::Panel::Seg13_Chance, 1);
      makeKnob(this, Vec(386.26, 313.57), Vampyre::Panel::Seg12_Length, 2);
      makeKnob(this, Vec(386.26, 91.57), Vampyre::Panel::Seg12_Chance, 1);
      makeKnob(this, Vec(360.47, 296.57), Vampyre::Panel::Seg11_Length, 2);
      makeKnob(this, Vec(360.47, 74.57), Vampyre::Panel::Seg11_Chance, 1);
      makeKnob(this, Vec(334.69, 313.57), Vampyre::Panel::Seg10_Length, 2);
      makeKnob(this, Vec(334.69, 91.57), Vampyre::Panel::Seg10_Chance, 1);
      makeKnob(this, Vec(308.90, 296.57), Vampyre::Panel::Seg09_Length, 2);
      makeKnob(this, Vec(308.90, 74.57), Vampyre::Panel::Seg09_Chance, 1);
      makeKnob(this, Vec(283.12, 313.34), Vampyre::Panel::Seg08_Length, 2);
      makeKnob(this, Vec(283.12, 91.34), Vampyre::Panel::Seg08_Chance, 1);
      makeKnob(this, Vec(257.33, 296.34), Vampyre::Panel::Seg07_Length, 2);
      makeKnob(this, Vec(257.33, 74.34), Vampyre::Panel::Seg07_Chance, 1);
      makeKnob(this, Vec(231.54, 313.34), Vampyre::Panel::Seg06_Length, 2);
      makeKnob(this, Vec(231.54, 91.34), Vampyre::Panel::Seg06_Chance, 1);
      makeKnob(this, Vec(205.76, 296.34), Vampyre::Panel::Seg05_Length, 2);
      makeKnob(this, Vec(205.76, 74.34), Vampyre::Panel::Seg05_Chance, 1);
      makeKnob(this, Vec(179.97, 313.34), Vampyre::Panel::Seg04_Length, 2);
      makeKnob(this, Vec(179.97, 91.34), Vampyre::Panel::Seg04_Chance, 1);
      makeKnob(this, Vec(154.18, 296.34), Vampyre::Panel::Seg03_Length, 2);
      makeKnob(this, Vec(154.18, 74.34), Vampyre::Panel::Seg03_Chance, 1);
      makeKnob(this, Vec(128.40, 313.34), Vampyre::Panel::Seg02_Length, 2);
      makeKnob(this, Vec(128.40, 91.34), Vampyre::Panel::Seg02_Chance, 1);
      makeKnob(this, Vec(102.61, 296.34), Vampyre::Panel::Seg01_Length, 2);
      makeKnob(this, Vec(102.61, 74.34), Vampyre::Panel::Seg01_Chance, 1);
      makeKnob(this, Vec(35.00, 99.80), Vampyre::Panel::Offset, 3);

      makeInput(this, Vec(35.00, 151.44),  Vampyre::Panel::BankSelect, false);

      makeOutput(this, Vec(35.00, 355.83), Vampyre::Panel::Gate, false);
      makeOutput(this, Vec(35.00, 310.08), Vampyre::Panel::Pitch, false);
      makeOutput(this, Vec(35.00, 247.42), Vampyre::Panel::First, false);

      makeLED(this, Vec(490.08, 57.75), Vampyre::Panel::RGB_Seg16_Current);
      makeLED(this, Vec(464.29, 57.75), Vampyre::Panel::RGB_Seg15_Current);
      makeLED(this, Vec(438.51, 57.75), Vampyre::Panel::RGB_Seg14_Current);
      makeLED(this, Vec(412.72, 57.75), Vampyre::Panel::RGB_Seg13_Current);
      makeLED(this, Vec(386.93, 57.75), Vampyre::Panel::RGB_Seg12_Current);
      makeLED(this, Vec(361.15, 57.75), Vampyre::Panel::RGB_Seg11_Current);
      makeLED(this, Vec(335.36, 57.75), Vampyre::Panel::RGB_Seg10_Current);
      makeLED(this, Vec(309.57, 57.75), Vampyre::Panel::RGB_Seg09_Current);
      makeLED(this, Vec(283.79, 57.52), Vampyre::Panel::RGB_Seg08_Current);
      makeLED(this, Vec(258.00, 57.52), Vampyre::Panel::RGB_Seg07_Current);
      makeLED(this, Vec(232.22, 57.52), Vampyre::Panel::RGB_Seg06_Current);
      makeLED(this, Vec(206.43, 57.52), Vampyre::Panel::RGB_Seg05_Current);
      makeLED(this, Vec(180.64, 57.52), Vampyre::Panel::RGB_Seg04_Current);
      makeLED(this, Vec(154.86, 57.52), Vampyre::Panel::RGB_Seg03_Current);
      makeLED(this, Vec(129.07, 57.52), Vampyre::Panel::RGB_Seg02_Current);
      makeLED(this, Vec(103.28, 57.52), Vampyre::Panel::RGB_Seg01_Current);

      makeLCD(this, Vec(10.00, 51.13), 3, Vampyre::Panel::Text_Bank, 18);
   }
}

#endif // NOT NosferatuVampyreHPP
