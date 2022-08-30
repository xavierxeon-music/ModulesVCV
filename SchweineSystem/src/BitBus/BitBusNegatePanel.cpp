#include "BitBusNegatePanel.h"
#include "BitBusNegate.h"

#include <SvinOrigin.h>

void BitBusNegate::setup()
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

void BitBusNegateWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusNegate.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(29.65, 336.97), BitBusNegate::Panel::Bit8_Latch, BitBusNegate::Panel::RGB_Bit8_Latch);
   makeLEDButton(this, Vec(29.65, 303.22), BitBusNegate::Panel::Bit7_Latch, BitBusNegate::Panel::RGB_Bit7_Latch);
   makeLEDButton(this, Vec(29.65, 267.94), BitBusNegate::Panel::Bit6_Latch, BitBusNegate::Panel::RGB_Bit6_Latch);
   makeLEDButton(this, Vec(29.65, 232.45), BitBusNegate::Panel::Bit5_Latch, BitBusNegate::Panel::RGB_Bit5_Latch);
   makeLEDButton(this, Vec(29.65, 164.33), BitBusNegate::Panel::Bit4_Latch, BitBusNegate::Panel::RGB_Bit4_Latch);
   makeLEDButton(this, Vec(29.65, 199.10), BitBusNegate::Panel::Bit3_Latch, BitBusNegate::Panel::RGB_Bit3_Latch);
   makeLEDButton(this, Vec(29.65, 129.96), BitBusNegate::Panel::Bit2_Latch, BitBusNegate::Panel::RGB_Bit2_Latch);
   makeLEDButton(this, Vec(29.65, 94.23), BitBusNegate::Panel::Bit1_Latch, BitBusNegate::Panel::RGB_Bit1_Latch);

   makeInput(this, Vec(61.19, 337.29), BitBusNegate::Panel::Bit8_GateIn, false);
   makeInput(this, Vec(61.19, 303.54), BitBusNegate::Panel::Bit7_GateIn, false);
   makeInput(this, Vec(61.19, 268.25), BitBusNegate::Panel::Bit6_GateIn, false);
   makeInput(this, Vec(61.19, 232.77), BitBusNegate::Panel::Bit5_GateIn, false);
   makeInput(this, Vec(61.19, 164.64), BitBusNegate::Panel::Bit4_GateIn, false);
   makeInput(this, Vec(61.19, 199.42), BitBusNegate::Panel::Bit3_GateIn, false);
   makeInput(this, Vec(61.19, 130.28), BitBusNegate::Panel::Bit2_GateIn, false);
   makeInput(this, Vec(61.19, 94.54), BitBusNegate::Panel::Bit1_GateIn, false);

   makeLED(this, Vec(9.92, 46.77), BitBusNegate::Panel::RGB_BusIn);
   makeLED(this, Vec(79.92, 46.77), BitBusNegate::Panel::RGB_BusOut);
}
