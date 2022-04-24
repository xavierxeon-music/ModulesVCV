#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include <SchweineSystemMaster.h>

void BitBusMeterAndFreeze::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::GateSample, "GateSample");
   configInput(Panel::GateFreeze, "GateFreeze");
}

void BitBusMeterAndFreezeWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusMeterAndFreeze.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(44.94, 244.95), BitBusMeterAndFreeze::Panel::FlipSample, BitBusMeterAndFreeze::Panel::RGB_FlipSample);
   makeLEDButton(this, Vec(44.94, 145.96), BitBusMeterAndFreeze::Panel::FlipFreeze, BitBusMeterAndFreeze::Panel::RGB_FlipFreeze);

   makeInput(this, Vec(44.94, 209.15),  BitBusMeterAndFreeze::Panel::GateSample);
   makeInput(this, Vec(44.94, 110.39),  BitBusMeterAndFreeze::Panel::GateFreeze);

   makeLight(this, Vec(13.82, 291.23), BitBusMeterAndFreeze::Panel::RGB_Bit8_Status1);
   makeLight(this, Vec(13.82, 257.59), BitBusMeterAndFreeze::Panel::RGB_Bit7_Status1);
   makeLight(this, Vec(13.82, 222.22), BitBusMeterAndFreeze::Panel::RGB_Bit6_Status1);
   makeLight(this, Vec(13.82, 187.06), BitBusMeterAndFreeze::Panel::RGB_Bit5_Status1);
   makeLight(this, Vec(13.82, 153.47), BitBusMeterAndFreeze::Panel::RGB_Bit4_Status1);
   makeLight(this, Vec(13.82, 118.69), BitBusMeterAndFreeze::Panel::RGB_Bit3_Status1);
   makeLight(this, Vec(13.82, 84.39), BitBusMeterAndFreeze::Panel::RGB_Bit2_Status1);
   makeLight(this, Vec(13.82, 48.73), BitBusMeterAndFreeze::Panel::RGB_Bit1_Status1);
   makeLight(this, Vec(14.35, 346.69), BitBusMeterAndFreeze::Panel::RGB_BusIn);
   makeLight(this, Vec(60.35, 346.69), BitBusMeterAndFreeze::Panel::RGB_BusOut);
}

