#ifndef BitBusMeterAndFreezeHPP
#define BitBusMeterAndFreezeHPP

#include "BitBusMeterAndFreeze.h"

#include <SvinOrigin.h>

namespace BitBus
{
   struct MeterAndFreeze::Panel
   {
      enum ParamId
      {
         // buttons
         // switches
         // ledbuttons
         FlipSample = 0,
         FlipFreeze = 1,
         // knobs
         // sliders
         PARAMS_LEN = 2
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
         GateSample = 0,
         GateFreeze = 1,
         INPUTS_LEN = 2
      };

      enum OutputId
      {
         OUTPUTS_LEN = 0
      };

      enum LightId
      {
         // leds
         RGB_Bit8_Status1 = 0,
         RGB_Bit7_Status1 = 3,
         RGB_Bit6_Status1 = 6,
         RGB_Bit5_Status1 = 9,
         RGB_Bit4_Status1 = 12,
         RGB_Bit3_Status1 = 15,
         RGB_Bit2_Status1 = 18,
         RGB_Bit1_Status1 = 21,
         RGB_BusIn = 24,
         RGB_BusOut = 27,
         // ledbuttons
         RGB_FlipSample = 30,
         RGB_FlipFreeze = 33,
         // sliders
         LIGHTS_LEN = 36
      };

   };

   void MeterAndFreeze::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

      configButton(Panel::FlipSample, "FlipSample");
      configButton(Panel::FlipFreeze, "FlipFreeze");

      configInput(Panel::GateSample, "GateSample");
      configInput(Panel::GateFreeze, "GateFreeze");
   }

   void MeterAndFreezeWidget::setup()
   {
      makePanel("res/BitBus/BitBusMeterAndFreeze.svg");

      makeLEDButton(this, Vec(44.94, 290.74), MeterAndFreeze::Panel::FlipSample, MeterAndFreeze::Panel::RGB_FlipSample);
      makeLEDButton(this, Vec(44.94, 191.75), MeterAndFreeze::Panel::FlipFreeze, MeterAndFreeze::Panel::RGB_FlipFreeze);

      makeInput(this, Vec(44.94, 254.94),  MeterAndFreeze::Panel::GateSample, true);
      makeInput(this, Vec(44.94, 156.19),  MeterAndFreeze::Panel::GateFreeze, true);

      makeLED(this, Vec(13.82, 337.02), MeterAndFreeze::Panel::RGB_Bit8_Status1);
      makeLED(this, Vec(13.82, 303.38), MeterAndFreeze::Panel::RGB_Bit7_Status1);
      makeLED(this, Vec(13.82, 268.01), MeterAndFreeze::Panel::RGB_Bit6_Status1);
      makeLED(this, Vec(13.82, 232.86), MeterAndFreeze::Panel::RGB_Bit5_Status1);
      makeLED(this, Vec(13.82, 199.26), MeterAndFreeze::Panel::RGB_Bit4_Status1);
      makeLED(this, Vec(13.82, 164.48), MeterAndFreeze::Panel::RGB_Bit3_Status1);
      makeLED(this, Vec(13.82, 130.19), MeterAndFreeze::Panel::RGB_Bit2_Status1);
      makeLED(this, Vec(13.82, 94.53), MeterAndFreeze::Panel::RGB_Bit1_Status1);
      makeLED(this, Vec(10.00, 46.77), MeterAndFreeze::Panel::RGB_BusIn);
      makeLED(this, Vec(65.00, 46.77), MeterAndFreeze::Panel::RGB_BusOut);
   }
}

#endif // NOT BitBusMeterAndFreezeHPP
