#ifndef BitBusNegateHPP
#define BitBusNegateHPP

#include "BitBusNegate.h"

#include <SvinOrigin.h>

namespace BitBus
{
   struct Negate::Panel
   {
      enum ParamId
      {
         // buttons
         // switches
         // ledbuttons
         Bit8_Latch = 0,
         Bit7_Latch = 1,
         Bit6_Latch = 2,
         Bit5_Latch = 3,
         Bit4_Latch = 4,
         Bit3_Latch = 5,
         Bit2_Latch = 6,
         Bit1_Latch = 7,
         // knobs
         // sliders
         PARAMS_LEN = 8
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
         Bit8_GateIn = 0,
         Bit7_GateIn = 1,
         Bit6_GateIn = 2,
         Bit5_GateIn = 3,
         Bit4_GateIn = 4,
         Bit3_GateIn = 5,
         Bit2_GateIn = 6,
         Bit1_GateIn = 7,
         INPUTS_LEN = 8
      };

      enum OutputId
      {
         OUTPUTS_LEN = 0
      };

      enum LightId
      {
         // leds
         RGB_BusIn = 0,
         RGB_BusOut = 3,
         // ledbuttons
         RGB_Bit8_Latch = 6,
         RGB_Bit7_Latch = 9,
         RGB_Bit6_Latch = 12,
         RGB_Bit5_Latch = 15,
         RGB_Bit4_Latch = 18,
         RGB_Bit3_Latch = 21,
         RGB_Bit2_Latch = 24,
         RGB_Bit1_Latch = 27,
         // sliders
         LIGHTS_LEN = 30
      };

   };

   void Negate::setup()
   {
      config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

      configButton(Panel::Bit8_Latch, "Bit8_Latch");
      configButton(Panel::Bit7_Latch, "Bit7_Latch");
      configButton(Panel::Bit6_Latch, "Bit6_Latch");
      configButton(Panel::Bit5_Latch, "Bit5_Latch");
      configButton(Panel::Bit4_Latch, "Bit4_Latch");
      configButton(Panel::Bit3_Latch, "Bit3_Latch");
      configButton(Panel::Bit2_Latch, "Bit2_Latch");
      configButton(Panel::Bit1_Latch, "Bit1_Latch");

      configInput(Panel::Bit8_GateIn, "Bit8_GateIn");
      configInput(Panel::Bit7_GateIn, "Bit7_GateIn");
      configInput(Panel::Bit6_GateIn, "Bit6_GateIn");
      configInput(Panel::Bit5_GateIn, "Bit5_GateIn");
      configInput(Panel::Bit4_GateIn, "Bit4_GateIn");
      configInput(Panel::Bit3_GateIn, "Bit3_GateIn");
      configInput(Panel::Bit2_GateIn, "Bit2_GateIn");
      configInput(Panel::Bit1_GateIn, "Bit1_GateIn");
   }

   void NegateWidget::setup()
   {
      std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusNegate.svg");
      SvgPanel* mainPanel = createPanel(panelPath);
      setPanel(mainPanel);

      makeLEDButton(this, Vec(29.65, 336.97), Negate::Panel::Bit8_Latch, Negate::Panel::RGB_Bit8_Latch);
      makeLEDButton(this, Vec(29.65, 303.22), Negate::Panel::Bit7_Latch, Negate::Panel::RGB_Bit7_Latch);
      makeLEDButton(this, Vec(29.65, 267.94), Negate::Panel::Bit6_Latch, Negate::Panel::RGB_Bit6_Latch);
      makeLEDButton(this, Vec(29.65, 232.45), Negate::Panel::Bit5_Latch, Negate::Panel::RGB_Bit5_Latch);
      makeLEDButton(this, Vec(29.65, 199.10), Negate::Panel::Bit4_Latch, Negate::Panel::RGB_Bit4_Latch);
      makeLEDButton(this, Vec(29.65, 164.33), Negate::Panel::Bit3_Latch, Negate::Panel::RGB_Bit3_Latch);
      makeLEDButton(this, Vec(29.65, 129.96), Negate::Panel::Bit2_Latch, Negate::Panel::RGB_Bit2_Latch);
      makeLEDButton(this, Vec(29.65, 94.23), Negate::Panel::Bit1_Latch, Negate::Panel::RGB_Bit1_Latch);

      makeInput(this, Vec(61.19, 337.29),  Negate::Panel::Bit8_GateIn, true);
      makeInput(this, Vec(61.19, 303.54),  Negate::Panel::Bit7_GateIn, true);
      makeInput(this, Vec(61.19, 268.25),  Negate::Panel::Bit6_GateIn, true);
      makeInput(this, Vec(61.19, 232.77),  Negate::Panel::Bit5_GateIn, true);
      makeInput(this, Vec(61.19, 199.42),  Negate::Panel::Bit4_GateIn, true);
      makeInput(this, Vec(61.19, 164.64),  Negate::Panel::Bit3_GateIn, true);
      makeInput(this, Vec(61.19, 130.28),  Negate::Panel::Bit2_GateIn, true);
      makeInput(this, Vec(61.19, 94.54),  Negate::Panel::Bit1_GateIn, true);

      makeLED(this, Vec(9.92, 46.77), Negate::Panel::RGB_BusIn);
      makeLED(this, Vec(79.92, 46.77), Negate::Panel::RGB_BusOut);
   }
}

#endif // NOT BitBusNegateHPP
