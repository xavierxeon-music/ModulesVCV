#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include <SchweineSystemMaster.h>

BitBusMeterAndFreeze::Panel::Panel()
{
};


void BitBusMeterAndFreeze::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::FlipSample, "FlipSample");
   configButton(Panel::FlipFreeze, "FlipFreeze");

   configInput(Panel::GateSample, "GateSample");
   configInput(Panel::GateFreeze, "GateFreeze");
}

SvgPanel* BitBusMeterAndFreezeWidget::setup(BitBusMeterAndFreeze* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusMeterAndFreeze.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(44.94, 244.95), BitBusMeterAndFreeze::Panel::FlipSample, BitBusMeterAndFreeze::Panel::Red_FlipSample);
   makeButton(this, Vec(44.94, 145.96), BitBusMeterAndFreeze::Panel::FlipFreeze, BitBusMeterAndFreeze::Panel::Red_FlipFreeze);

   makeInput(this, Vec(44.94, 209.15),  BitBusMeterAndFreeze::Panel::GateSample);
   makeInput(this, Vec(44.94, 110.39),  BitBusMeterAndFreeze::Panel::GateFreeze);

   makeLight(this, Vec(13.82, 291.23), BitBusMeterAndFreeze::Panel::Red_Bit8_Status1);
   makeLight(this, Vec(13.82, 257.59), BitBusMeterAndFreeze::Panel::Red_Bit7_Status1);
   makeLight(this, Vec(13.82, 222.22), BitBusMeterAndFreeze::Panel::Red_Bit6_Status1);
   makeLight(this, Vec(13.82, 187.06), BitBusMeterAndFreeze::Panel::Red_Bit5_Status1);
   makeLight(this, Vec(13.82, 153.47), BitBusMeterAndFreeze::Panel::Red_Bit4_Status1);
   makeLight(this, Vec(13.82, 118.69), BitBusMeterAndFreeze::Panel::Red_Bit3_Status1);
   makeLight(this, Vec(13.82, 84.39), BitBusMeterAndFreeze::Panel::Red_Bit2_Status1);
   makeLight(this, Vec(13.82, 48.73), BitBusMeterAndFreeze::Panel::Red_Bit1_Status1);
   makeLight(this, Vec(14.35, 346.69), BitBusMeterAndFreeze::Panel::Red_BusIn);
   makeLight(this, Vec(60.35, 346.69), BitBusMeterAndFreeze::Panel::Red_BusOut);

   return mainPanel;
}

