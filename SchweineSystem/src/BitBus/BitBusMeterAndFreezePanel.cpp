#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include <SvinOrigin.h>

void BitBusMeterAndFreeze::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::FlipSample, "FlipSample");
   configButton(Panel::FlipFreeze, "FlipFreeze");

   configInput(Panel::GateSample, "GateSample");
   configInput(Panel::GateFreeze, "GateFreeze");
}

void BitBusMeterAndFreezeWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/BitBus/BitBusMeterAndFreeze.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(44.94, 290.74), BitBusMeterAndFreeze::Panel::FlipSample, BitBusMeterAndFreeze::Panel::RGB_FlipSample);
   makeLEDButton(this, Vec(44.94, 191.75), BitBusMeterAndFreeze::Panel::FlipFreeze, BitBusMeterAndFreeze::Panel::RGB_FlipFreeze);

   makeInput(this, Vec(44.94, 254.94),  BitBusMeterAndFreeze::Panel::GateSample, true);
   makeInput(this, Vec(44.94, 156.19),  BitBusMeterAndFreeze::Panel::GateFreeze, true);

   makeLED(this, Vec(13.82, 337.02), BitBusMeterAndFreeze::Panel::RGB_Bit8_Status1);
   makeLED(this, Vec(13.82, 303.38), BitBusMeterAndFreeze::Panel::RGB_Bit7_Status1);
   makeLED(this, Vec(13.82, 268.01), BitBusMeterAndFreeze::Panel::RGB_Bit6_Status1);
   makeLED(this, Vec(13.82, 232.86), BitBusMeterAndFreeze::Panel::RGB_Bit5_Status1);
   makeLED(this, Vec(13.82, 199.26), BitBusMeterAndFreeze::Panel::RGB_Bit4_Status1);
   makeLED(this, Vec(13.82, 164.48), BitBusMeterAndFreeze::Panel::RGB_Bit3_Status1);
   makeLED(this, Vec(13.82, 130.19), BitBusMeterAndFreeze::Panel::RGB_Bit2_Status1);
   makeLED(this, Vec(13.82, 94.53), BitBusMeterAndFreeze::Panel::RGB_Bit1_Status1);
   makeLED(this, Vec(10.00, 46.77), BitBusMeterAndFreeze::Panel::RGB_BusIn);
   makeLED(this, Vec(65.00, 46.77), BitBusMeterAndFreeze::Panel::RGB_BusOut);
}

