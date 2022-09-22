#ifndef NosferatuAcolyteHPP
#define NosferatuAcolyteHPP

#include "NosferatuAcolyte.h"

#include <SvinOrigin.h>

namespace Nosferatu
{
   struct Acolyte::Panel
   {
      enum ParamId
      {
         // buttons
         // switches
         // ledbuttons
         Seg08_Active = 0,
         Seg07_Active = 1,
         Seg06_Active = 2,
         Seg05_Active = 3,
         Seg04_Active = 4,
         Seg03_Active = 5,
         Seg02_Active = 6,
         Seg01_Active = 7,
         // knobs
         Seg08_Length = 8,
         Seg08_Chance = 9,
         Seg07_Length = 10,
         Seg07_Chance = 11,
         Seg06_Length = 12,
         Seg06_Chance = 13,
         Seg05_Length = 14,
         Seg05_Chance = 15,
         Seg04_Length = 16,
         Seg04_Chance = 17,
         Seg03_Length = 18,
         Seg03_Chance = 19,
         Seg02_Length = 20,
         Seg02_Chance = 21,
         Seg01_Length = 22,
         Seg01_Chance = 23,
         // sliders
         Seg08_Ticks = 24,
         Seg08_Pitch = 25,
         Seg07_Ticks = 26,
         Seg07_Pitch = 27,
         Seg06_Ticks = 28,
         Seg06_Pitch = 29,
         Seg05_Ticks = 30,
         Seg05_Pitch = 31,
         Seg04_Ticks = 32,
         Seg04_Pitch = 33,
         Seg03_Ticks = 34,
         Seg03_Pitch = 35,
         Seg02_Ticks = 36,
         Seg02_Pitch = 37,
         Seg01_Ticks = 38,
         Seg01_Pitch = 39,
         PARAMS_LEN = 40
      };

      enum DisplayId
      {
         // lcd
         Text_Number = 0,
         // oled
         DISPLAYS_LEN = 1
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
         OUTPUTS_LEN = 0
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

   void Acolyte::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

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
   }

   void AcolyteWidget::setup()
   {
      std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Sequencer/NosferatuAcolyte.svg");
      SvgPanel* mainPanel = createPanel(panelPath);
      setPanel(mainPanel);

      makeSlider(this, Vec(200.40, 235.45), NosferatuAcolyte::Panel::Seg08_Ticks, NosferatuAcolyte::Panel::RGB_Seg08_Ticks);
      makeSlider(this, Vec(200.40, 143.82), NosferatuAcolyte::Panel::Seg08_Pitch, NosferatuAcolyte::Panel::RGB_Seg08_Pitch);
      makeSlider(this, Vec(174.62, 235.45), NosferatuAcolyte::Panel::Seg07_Ticks, NosferatuAcolyte::Panel::RGB_Seg07_Ticks);
      makeSlider(this, Vec(174.62, 143.82), NosferatuAcolyte::Panel::Seg07_Pitch, NosferatuAcolyte::Panel::RGB_Seg07_Pitch);
      makeSlider(this, Vec(148.83, 235.45), NosferatuAcolyte::Panel::Seg06_Ticks, NosferatuAcolyte::Panel::RGB_Seg06_Ticks);
      makeSlider(this, Vec(148.83, 143.82), NosferatuAcolyte::Panel::Seg06_Pitch, NosferatuAcolyte::Panel::RGB_Seg06_Pitch);
      makeSlider(this, Vec(123.04, 235.45), NosferatuAcolyte::Panel::Seg05_Ticks, NosferatuAcolyte::Panel::RGB_Seg05_Ticks);
      makeSlider(this, Vec(123.04, 143.82), NosferatuAcolyte::Panel::Seg05_Pitch, NosferatuAcolyte::Panel::RGB_Seg05_Pitch);
      makeSlider(this, Vec(97.26, 235.45), NosferatuAcolyte::Panel::Seg04_Ticks, NosferatuAcolyte::Panel::RGB_Seg04_Ticks);
      makeSlider(this, Vec(97.26, 143.82), NosferatuAcolyte::Panel::Seg04_Pitch, NosferatuAcolyte::Panel::RGB_Seg04_Pitch);
      makeSlider(this, Vec(71.47, 235.45), NosferatuAcolyte::Panel::Seg03_Ticks, NosferatuAcolyte::Panel::RGB_Seg03_Ticks);
      makeSlider(this, Vec(71.47, 143.82), NosferatuAcolyte::Panel::Seg03_Pitch, NosferatuAcolyte::Panel::RGB_Seg03_Pitch);
      makeSlider(this, Vec(45.68, 235.45), NosferatuAcolyte::Panel::Seg02_Ticks, NosferatuAcolyte::Panel::RGB_Seg02_Ticks);
      makeSlider(this, Vec(45.68, 143.82), NosferatuAcolyte::Panel::Seg02_Pitch, NosferatuAcolyte::Panel::RGB_Seg02_Pitch);
      makeSlider(this, Vec(19.90, 235.45), NosferatuAcolyte::Panel::Seg01_Ticks, NosferatuAcolyte::Panel::RGB_Seg01_Ticks);
      makeSlider(this, Vec(19.90, 143.82), NosferatuAcolyte::Panel::Seg01_Pitch, NosferatuAcolyte::Panel::RGB_Seg01_Pitch);

      makeLEDButton(this, Vec(200.40, 343.94), NosferatuAcolyte::Panel::Seg08_Active, NosferatuAcolyte::Panel::RGB_Seg08_Active);
      makeLEDButton(this, Vec(174.62, 343.94), NosferatuAcolyte::Panel::Seg07_Active, NosferatuAcolyte::Panel::RGB_Seg07_Active);
      makeLEDButton(this, Vec(148.83, 343.94), NosferatuAcolyte::Panel::Seg06_Active, NosferatuAcolyte::Panel::RGB_Seg06_Active);
      makeLEDButton(this, Vec(123.04, 343.94), NosferatuAcolyte::Panel::Seg05_Active, NosferatuAcolyte::Panel::RGB_Seg05_Active);
      makeLEDButton(this, Vec(97.26, 343.94), NosferatuAcolyte::Panel::Seg04_Active, NosferatuAcolyte::Panel::RGB_Seg04_Active);
      makeLEDButton(this, Vec(71.47, 343.94), NosferatuAcolyte::Panel::Seg03_Active, NosferatuAcolyte::Panel::RGB_Seg03_Active);
      makeLEDButton(this, Vec(45.68, 343.94), NosferatuAcolyte::Panel::Seg02_Active, NosferatuAcolyte::Panel::RGB_Seg02_Active);
      makeLEDButton(this, Vec(19.90, 343.94), NosferatuAcolyte::Panel::Seg01_Active, NosferatuAcolyte::Panel::RGB_Seg01_Active);

      makeKnob(this, Vec(199.73, 313.34), NosferatuAcolyte::Panel::Seg08_Length, 2);
      makeKnob(this, Vec(199.73, 91.34), NosferatuAcolyte::Panel::Seg08_Chance, 1);
      makeKnob(this, Vec(173.94, 296.34), NosferatuAcolyte::Panel::Seg07_Length, 2);
      makeKnob(this, Vec(173.94, 74.34), NosferatuAcolyte::Panel::Seg07_Chance, 1);
      makeKnob(this, Vec(148.16, 313.34), NosferatuAcolyte::Panel::Seg06_Length, 2);
      makeKnob(this, Vec(148.16, 91.34), NosferatuAcolyte::Panel::Seg06_Chance, 1);
      makeKnob(this, Vec(122.37, 296.34), NosferatuAcolyte::Panel::Seg05_Length, 2);
      makeKnob(this, Vec(122.37, 74.34), NosferatuAcolyte::Panel::Seg05_Chance, 1);
      makeKnob(this, Vec(96.58, 313.34), NosferatuAcolyte::Panel::Seg04_Length, 2);
      makeKnob(this, Vec(96.58, 91.34), NosferatuAcolyte::Panel::Seg04_Chance, 1);
      makeKnob(this, Vec(70.80, 296.34), NosferatuAcolyte::Panel::Seg03_Length, 2);
      makeKnob(this, Vec(70.80, 74.34), NosferatuAcolyte::Panel::Seg03_Chance, 1);
      makeKnob(this, Vec(45.01, 313.34), NosferatuAcolyte::Panel::Seg02_Length, 2);
      makeKnob(this, Vec(45.01, 91.34), NosferatuAcolyte::Panel::Seg02_Chance, 1);
      makeKnob(this, Vec(19.23, 296.34), NosferatuAcolyte::Panel::Seg01_Length, 2);
      makeKnob(this, Vec(19.23, 74.34), NosferatuAcolyte::Panel::Seg01_Chance, 1);

      makeLED(this, Vec(200.40, 57.52), NosferatuAcolyte::Panel::RGB_Seg08_Current);
      makeLED(this, Vec(174.62, 57.52), NosferatuAcolyte::Panel::RGB_Seg07_Current);
      makeLED(this, Vec(148.83, 57.52), NosferatuAcolyte::Panel::RGB_Seg06_Current);
      makeLED(this, Vec(123.04, 57.52), NosferatuAcolyte::Panel::RGB_Seg05_Current);
      makeLED(this, Vec(97.26, 57.52), NosferatuAcolyte::Panel::RGB_Seg04_Current);
      makeLED(this, Vec(71.47, 57.52), NosferatuAcolyte::Panel::RGB_Seg03_Current);
      makeLED(this, Vec(45.68, 57.52), NosferatuAcolyte::Panel::RGB_Seg02_Current);
      makeLED(this, Vec(19.90, 57.52), NosferatuAcolyte::Panel::RGB_Seg01_Current);

      makeLCD(this, Vec(13.37, 10.00), 3, NosferatuAcolyte::Panel::Text_Number, 18);
   }
}

#endif // NOT NosferatuAcolyteHPP
