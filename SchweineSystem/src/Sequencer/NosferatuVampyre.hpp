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
         Seg08_Active = 2,
         Seg07_Active = 3,
         Seg06_Active = 4,
         Seg05_Active = 5,
         Seg04_Active = 6,
         Seg03_Active = 7,
         Seg02_Active = 8,
         Seg01_Active = 9,
         // knobs
         Seg08_Length = 10,
         Seg08_Chance = 11,
         Seg07_Length = 12,
         Seg07_Chance = 13,
         Seg06_Length = 14,
         Seg06_Chance = 15,
         Seg05_Length = 16,
         Seg05_Chance = 17,
         Seg04_Length = 18,
         Seg04_Chance = 19,
         Seg03_Length = 20,
         Seg03_Chance = 21,
         Seg02_Length = 22,
         Seg02_Chance = 23,
         Seg01_Length = 24,
         Seg01_Chance = 25,
         Offset = 26,
         // sliders
         Seg08_Ticks = 27,
         Seg08_Pitch = 28,
         Seg07_Ticks = 29,
         Seg07_Pitch = 30,
         Seg06_Ticks = 31,
         Seg06_Pitch = 32,
         Seg05_Ticks = 33,
         Seg05_Pitch = 34,
         Seg04_Ticks = 35,
         Seg04_Pitch = 36,
         Seg03_Ticks = 37,
         Seg03_Pitch = 38,
         Seg02_Ticks = 39,
         Seg02_Pitch = 40,
         Seg01_Ticks = 41,
         Seg01_Pitch = 42,
         PARAMS_LEN = 43
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
         RGB_Seg08_Current = 0,
         RGB_Seg07_Current = 3,
         RGB_Seg06_Current = 6,
         RGB_Seg05_Current = 9,
         RGB_Seg04_Current = 12,
         RGB_Seg03_Current = 15,
         RGB_Seg02_Current = 18,
         RGB_Seg01_Current = 21,
         // ledbuttons
         RGB_Seg08_Active = 24,
         RGB_Seg07_Active = 27,
         RGB_Seg06_Active = 30,
         RGB_Seg05_Active = 33,
         RGB_Seg04_Active = 36,
         RGB_Seg03_Active = 39,
         RGB_Seg02_Active = 42,
         RGB_Seg01_Active = 45,
         // sliders
         RGB_Seg08_Ticks = 48,
         RGB_Seg08_Pitch = 51,
         RGB_Seg07_Ticks = 54,
         RGB_Seg07_Pitch = 57,
         RGB_Seg06_Ticks = 60,
         RGB_Seg06_Pitch = 63,
         RGB_Seg05_Ticks = 66,
         RGB_Seg05_Pitch = 69,
         RGB_Seg04_Ticks = 72,
         RGB_Seg04_Pitch = 75,
         RGB_Seg03_Ticks = 78,
         RGB_Seg03_Pitch = 81,
         RGB_Seg02_Ticks = 84,
         RGB_Seg02_Pitch = 87,
         RGB_Seg01_Ticks = 90,
         RGB_Seg01_Pitch = 93,
         LIGHTS_LEN = 96
      };

   };

   void Vampyre::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

      configButton(Panel::Down, "Down");
      configButton(Panel::Up, "Up");

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

      configButton(Panel::Seg08_Active, "Seg08_Active");
      configButton(Panel::Seg07_Active, "Seg07_Active");
      configButton(Panel::Seg06_Active, "Seg06_Active");
      configButton(Panel::Seg05_Active, "Seg05_Active");
      configButton(Panel::Seg04_Active, "Seg04_Active");
      configButton(Panel::Seg03_Active, "Seg03_Active");
      configButton(Panel::Seg02_Active, "Seg02_Active");
      configButton(Panel::Seg01_Active, "Seg01_Active");

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

      makeSlider(this, Vec(295.10, 235.72), Vampyre::Panel::Seg08_Ticks, Vampyre::Panel::RGB_Seg08_Ticks);
      makeSlider(this, Vec(295.10, 144.09), Vampyre::Panel::Seg08_Pitch, Vampyre::Panel::RGB_Seg08_Pitch);
      makeSlider(this, Vec(269.32, 235.72), Vampyre::Panel::Seg07_Ticks, Vampyre::Panel::RGB_Seg07_Ticks);
      makeSlider(this, Vec(269.32, 144.09), Vampyre::Panel::Seg07_Pitch, Vampyre::Panel::RGB_Seg07_Pitch);
      makeSlider(this, Vec(243.53, 235.72), Vampyre::Panel::Seg06_Ticks, Vampyre::Panel::RGB_Seg06_Ticks);
      makeSlider(this, Vec(243.53, 144.09), Vampyre::Panel::Seg06_Pitch, Vampyre::Panel::RGB_Seg06_Pitch);
      makeSlider(this, Vec(217.74, 235.72), Vampyre::Panel::Seg05_Ticks, Vampyre::Panel::RGB_Seg05_Ticks);
      makeSlider(this, Vec(217.74, 144.09), Vampyre::Panel::Seg05_Pitch, Vampyre::Panel::RGB_Seg05_Pitch);
      makeSlider(this, Vec(191.96, 235.72), Vampyre::Panel::Seg04_Ticks, Vampyre::Panel::RGB_Seg04_Ticks);
      makeSlider(this, Vec(191.96, 144.09), Vampyre::Panel::Seg04_Pitch, Vampyre::Panel::RGB_Seg04_Pitch);
      makeSlider(this, Vec(166.17, 235.72), Vampyre::Panel::Seg03_Ticks, Vampyre::Panel::RGB_Seg03_Ticks);
      makeSlider(this, Vec(166.17, 144.09), Vampyre::Panel::Seg03_Pitch, Vampyre::Panel::RGB_Seg03_Pitch);
      makeSlider(this, Vec(140.38, 235.72), Vampyre::Panel::Seg02_Ticks, Vampyre::Panel::RGB_Seg02_Ticks);
      makeSlider(this, Vec(140.38, 144.09), Vampyre::Panel::Seg02_Pitch, Vampyre::Panel::RGB_Seg02_Pitch);
      makeSlider(this, Vec(114.60, 235.72), Vampyre::Panel::Seg01_Ticks, Vampyre::Panel::RGB_Seg01_Ticks);
      makeSlider(this, Vec(114.60, 144.09), Vampyre::Panel::Seg01_Pitch, Vampyre::Panel::RGB_Seg01_Pitch);

      makeLEDButton(this, Vec(295.10, 344.21), Vampyre::Panel::Seg08_Active, Vampyre::Panel::RGB_Seg08_Active);
      makeLEDButton(this, Vec(269.32, 344.21), Vampyre::Panel::Seg07_Active, Vampyre::Panel::RGB_Seg07_Active);
      makeLEDButton(this, Vec(243.53, 344.21), Vampyre::Panel::Seg06_Active, Vampyre::Panel::RGB_Seg06_Active);
      makeLEDButton(this, Vec(217.74, 344.21), Vampyre::Panel::Seg05_Active, Vampyre::Panel::RGB_Seg05_Active);
      makeLEDButton(this, Vec(191.96, 344.21), Vampyre::Panel::Seg04_Active, Vampyre::Panel::RGB_Seg04_Active);
      makeLEDButton(this, Vec(166.17, 344.21), Vampyre::Panel::Seg03_Active, Vampyre::Panel::RGB_Seg03_Active);
      makeLEDButton(this, Vec(140.38, 344.21), Vampyre::Panel::Seg02_Active, Vampyre::Panel::RGB_Seg02_Active);
      makeLEDButton(this, Vec(114.60, 344.21), Vampyre::Panel::Seg01_Active, Vampyre::Panel::RGB_Seg01_Active);

      makeKnob(this, Vec(294.43, 313.61), Vampyre::Panel::Seg08_Length, 2);
      makeKnob(this, Vec(294.43, 91.61), Vampyre::Panel::Seg08_Chance, 1);
      makeKnob(this, Vec(268.64, 296.61), Vampyre::Panel::Seg07_Length, 2);
      makeKnob(this, Vec(268.64, 74.61), Vampyre::Panel::Seg07_Chance, 1);
      makeKnob(this, Vec(242.86, 313.61), Vampyre::Panel::Seg06_Length, 2);
      makeKnob(this, Vec(242.86, 91.61), Vampyre::Panel::Seg06_Chance, 1);
      makeKnob(this, Vec(217.07, 296.61), Vampyre::Panel::Seg05_Length, 2);
      makeKnob(this, Vec(217.07, 74.61), Vampyre::Panel::Seg05_Chance, 1);
      makeKnob(this, Vec(191.28, 313.61), Vampyre::Panel::Seg04_Length, 2);
      makeKnob(this, Vec(191.28, 91.61), Vampyre::Panel::Seg04_Chance, 1);
      makeKnob(this, Vec(165.50, 296.61), Vampyre::Panel::Seg03_Length, 2);
      makeKnob(this, Vec(165.50, 74.61), Vampyre::Panel::Seg03_Chance, 1);
      makeKnob(this, Vec(139.71, 313.61), Vampyre::Panel::Seg02_Length, 2);
      makeKnob(this, Vec(139.71, 91.61), Vampyre::Panel::Seg02_Chance, 1);
      makeKnob(this, Vec(113.93, 296.61), Vampyre::Panel::Seg01_Length, 2);
      makeKnob(this, Vec(113.93, 74.61), Vampyre::Panel::Seg01_Chance, 1);
      makeKnob(this, Vec(35.00, 99.80), Vampyre::Panel::Offset, 3);

      makeInput(this, Vec(35.00, 151.44),  Vampyre::Panel::BankSelect, false);

      makeOutput(this, Vec(35.00, 355.83), Vampyre::Panel::Gate, false);
      makeOutput(this, Vec(35.00, 310.08), Vampyre::Panel::Pitch, false);
      makeOutput(this, Vec(35.00, 247.42), Vampyre::Panel::First, false);

      makeLED(this, Vec(295.10, 57.79), Vampyre::Panel::RGB_Seg08_Current);
      makeLED(this, Vec(269.32, 57.79), Vampyre::Panel::RGB_Seg07_Current);
      makeLED(this, Vec(243.53, 57.79), Vampyre::Panel::RGB_Seg06_Current);
      makeLED(this, Vec(217.74, 57.79), Vampyre::Panel::RGB_Seg05_Current);
      makeLED(this, Vec(191.96, 57.79), Vampyre::Panel::RGB_Seg04_Current);
      makeLED(this, Vec(166.17, 57.79), Vampyre::Panel::RGB_Seg03_Current);
      makeLED(this, Vec(140.39, 57.79), Vampyre::Panel::RGB_Seg02_Current);
      makeLED(this, Vec(114.60, 57.79), Vampyre::Panel::RGB_Seg01_Current);

      makeLCD(this, Vec(10.00, 51.13), 3, Vampyre::Panel::Text_Bank, 18);
   }
}

#endif // NOT NosferatuVampyreHPP
