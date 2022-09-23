#ifndef BitBusCounterHPP
#define BitBusCounterHPP

#include "BitBusCounter.h"

#include <SvinOrigin.h>

namespace BitBus
{
   struct Counter::Panel
   {
      enum ParamId
      {
         // buttons
         // switches
         // ledbuttons
         // knobs
         // sliders
         Threshold = 0,
         PARAMS_LEN = 1
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
         Reset = 0,
         Down = 1,
         Up = 2,
         INPUTS_LEN = 3
      };

      enum OutputId
      {
         OUTPUTS_LEN = 0
      };

      enum LightId
      {
         // leds
         RGB_Bit8_Indicator = 0,
         RGB_Bit7_Indicator = 3,
         RGB_Bit6_Indicator = 6,
         RGB_Bit5_Indicator = 9,
         RGB_Bit4_Indicator = 12,
         RGB_Bit3_Indicator = 15,
         RGB_Bit2_Indicator = 18,
         RGB_Bit1_Indicator = 21,
         RGB_BusOut = 24,
         // ledbuttons
         // sliders
         RGB_Threshold = 27,
         LIGHTS_LEN = 30
      };

   };

   void Counter::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

      configSwitch(Panel::Threshold, 0.0f, 1.0f, 0.0f, "Threshold");

      configInput(Panel::Reset, "Reset");
      configInput(Panel::Down, "Down");
      configInput(Panel::Up, "Up");
   }

   void CounterWidget::setup()
   {
      makePanel("res/BitBus/BitBusCounter.svg");

      makeSlider(this, Vec(23.72, 130.24), Counter::Panel::Threshold, Counter::Panel::RGB_Threshold);

      makeInput(this, Vec(23.72, 344.87),  Counter::Panel::Reset, false);
      makeInput(this, Vec(23.72, 261.44),  Counter::Panel::Down, false);
      makeInput(this, Vec(23.72, 205.64),  Counter::Panel::Up, false);

      makeLED(this, Vec(65.77, 337.02), Counter::Panel::RGB_Bit8_Indicator);
      makeLED(this, Vec(65.77, 303.38), Counter::Panel::RGB_Bit7_Indicator);
      makeLED(this, Vec(65.77, 268.01), Counter::Panel::RGB_Bit6_Indicator);
      makeLED(this, Vec(65.77, 232.71), Counter::Panel::RGB_Bit5_Indicator);
      makeLED(this, Vec(65.77, 199.26), Counter::Panel::RGB_Bit4_Indicator);
      makeLED(this, Vec(65.77, 164.48), Counter::Panel::RGB_Bit3_Indicator);
      makeLED(this, Vec(65.77, 130.11), Counter::Panel::RGB_Bit2_Indicator);
      makeLED(this, Vec(65.77, 94.53), Counter::Panel::RGB_Bit1_Indicator);
      makeLED(this, Vec(79.92, 46.77), Counter::Panel::RGB_BusOut);

      makeLCD(this, Vec(20.00, 42.49), 3, Counter::Panel::Text_Number, 18);
   }
}

#endif // NOT BitBusCounterHPP
