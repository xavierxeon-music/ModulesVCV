#include "BitBusNegate.h"
#include "BitBusNegatePanel.h"

#include <SchweineSystemMaster.h>

void BitBusNegate::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

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
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusNegate.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(29.23, 291.18), BitBusNegate::Panel::Bit8_Latch, BitBusNegate::Panel::RGB_Bit8_Latch);
   makeLEDButton(this, Vec(29.23, 257.43), BitBusNegate::Panel::Bit7_Latch, BitBusNegate::Panel::RGB_Bit7_Latch);
   makeLEDButton(this, Vec(29.23, 222.15), BitBusNegate::Panel::Bit6_Latch, BitBusNegate::Panel::RGB_Bit6_Latch);
   makeLEDButton(this, Vec(29.23, 186.66), BitBusNegate::Panel::Bit5_Latch, BitBusNegate::Panel::RGB_Bit5_Latch);
   makeLEDButton(this, Vec(29.23, 118.53), BitBusNegate::Panel::Bit4_Latch, BitBusNegate::Panel::RGB_Bit4_Latch);
   makeLEDButton(this, Vec(29.23, 153.31), BitBusNegate::Panel::Bit3_Latch, BitBusNegate::Panel::RGB_Bit3_Latch);
   makeLEDButton(this, Vec(29.23, 84.17), BitBusNegate::Panel::Bit2_Latch, BitBusNegate::Panel::RGB_Bit2_Latch);
   makeLEDButton(this, Vec(29.23, 48.43), BitBusNegate::Panel::Bit1_Latch, BitBusNegate::Panel::RGB_Bit1_Latch);

   makeInput(this, Vec(60.77, 291.50),  BitBusNegate::Panel::Bit8_GateIn);
   makeInput(this, Vec(60.77, 257.74),  BitBusNegate::Panel::Bit7_GateIn);
   makeInput(this, Vec(60.77, 222.46),  BitBusNegate::Panel::Bit6_GateIn);
   makeInput(this, Vec(60.77, 186.97),  BitBusNegate::Panel::Bit5_GateIn);
   makeInput(this, Vec(60.77, 118.85),  BitBusNegate::Panel::Bit4_GateIn);
   makeInput(this, Vec(60.77, 153.62),  BitBusNegate::Panel::Bit3_GateIn);
   makeInput(this, Vec(60.77, 84.49),  BitBusNegate::Panel::Bit2_GateIn);
   makeInput(this, Vec(60.77, 48.75),  BitBusNegate::Panel::Bit1_GateIn);

   makeLED(this, Vec(14.35, 346.69), BitBusNegate::Panel::RGB_BusIn);
   makeLED(this, Vec(75.35, 346.69), BitBusNegate::Panel::RGB_BusOut);
}

