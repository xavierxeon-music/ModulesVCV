#include "BitBusMeterAndFreezePanel.h"
#include "BitBusMeterAndFreeze.h"

#include "SchweineSystemMaster.h"

void BitBusMeterAndFreeze::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::FlipSample, "FlipSample");
   configButton(Panel::FlipFreeze, "FlipFreeze");

   configInput(Panel::GateSample, "GateSample");
   configInput(Panel::GateFreeze, "GateFreeze");
}

BitBusMeterAndFreezeWidget::BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusMeterAndFreeze.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(89.942439668, 244.94665081), module, BitBusMeterAndFreeze::Panel::FlipSample, BitBusMeterAndFreeze::Panel::Red_FlipSample));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(89.942439668, 145.95655081), module, BitBusMeterAndFreeze::Panel::FlipFreeze, BitBusMeterAndFreeze::Panel::Red_FlipFreeze));

   addInput(createInputCentered<PJ301MPort>(Vec(89.942439668, 209.14595081), module, BitBusMeterAndFreeze::Panel::GateSample));
   addInput(createInputCentered<PJ301MPort>(Vec(89.942439668, 110.39405081), module, BitBusMeterAndFreeze::Panel::GateFreeze));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(51.47269458249998, 291.226), module, BitBusMeterAndFreeze::Panel::Red_Bit8_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.05966958249998, 291.226), module, BitBusMeterAndFreeze::Panel::Red_Bit8_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(32.646569582499964, 291.226), module, BitBusMeterAndFreeze::Panel::Red_Bit8_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(23.23354458249996, 291.226), module, BitBusMeterAndFreeze::Panel::Red_Bit8_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(13.820444582499974, 291.226), module, BitBusMeterAndFreeze::Panel::Red_Bit8_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(51.47111488750001, 257.587), module, BitBusMeterAndFreeze::Panel::Red_Bit7_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.0580898875, 257.587), module, BitBusMeterAndFreeze::Panel::Red_Bit7_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(32.64498988749999, 257.587), module, BitBusMeterAndFreeze::Panel::Red_Bit7_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(23.231964887499984, 257.587), module, BitBusMeterAndFreeze::Panel::Red_Bit7_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(13.818864887499984, 257.587), module, BitBusMeterAndFreeze::Panel::Red_Bit7_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(51.47111488750001, 222.219), module, BitBusMeterAndFreeze::Panel::Red_Bit6_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.0580898875, 222.219), module, BitBusMeterAndFreeze::Panel::Red_Bit6_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(32.64498988749999, 222.219), module, BitBusMeterAndFreeze::Panel::Red_Bit6_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(23.231964887499984, 222.219), module, BitBusMeterAndFreeze::Panel::Red_Bit6_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(13.818864887499984, 222.219), module, BitBusMeterAndFreeze::Panel::Red_Bit6_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(51.47111814190255, 187.08440291946394), module, BitBusMeterAndFreeze::Panel::Red_Bit5_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.058488488952534, 186.99801505952644), module, BitBusMeterAndFreeze::Panel::Red_Bit5_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(32.64578383915253, 186.91162651127786), module, BitBusMeterAndFreeze::Panel::Red_Bit5_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(23.233154186202526, 186.82523865134038), module, BitBusMeterAndFreeze::Panel::Red_Bit5_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(13.820449536402528, 186.7388501030918), module, BitBusMeterAndFreeze::Panel::Red_Bit5_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(51.472694582499955, 153.46499999999997), module, BitBusMeterAndFreeze::Panel::Red_Bit4_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.05966958249995, 153.46499999999997), module, BitBusMeterAndFreeze::Panel::Red_Bit4_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(32.64656958249995, 153.46499999999997), module, BitBusMeterAndFreeze::Panel::Red_Bit4_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(23.233544582499945, 153.46499999999997), module, BitBusMeterAndFreeze::Panel::Red_Bit4_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(13.820444582499945, 153.46499999999997), module, BitBusMeterAndFreeze::Panel::Red_Bit4_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(51.47269458249998, 118.68969999999999), module, BitBusMeterAndFreeze::Panel::Red_Bit3_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.05966958249998, 118.68969999999999), module, BitBusMeterAndFreeze::Panel::Red_Bit3_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(32.646569582499964, 118.68969999999999), module, BitBusMeterAndFreeze::Panel::Red_Bit3_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(23.23354458249996, 118.68969999999999), module, BitBusMeterAndFreeze::Panel::Red_Bit3_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(13.820444582499974, 118.68969999999999), module, BitBusMeterAndFreeze::Panel::Red_Bit3_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(51.47269458249998, 84.39249999999998), module, BitBusMeterAndFreeze::Panel::Red_Bit2_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.05966958249998, 84.39249999999998), module, BitBusMeterAndFreeze::Panel::Red_Bit2_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(32.646569582499964, 84.39249999999998), module, BitBusMeterAndFreeze::Panel::Red_Bit2_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(23.23354458249996, 84.39249999999998), module, BitBusMeterAndFreeze::Panel::Red_Bit2_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(13.820444582499974, 84.39249999999998), module, BitBusMeterAndFreeze::Panel::Red_Bit2_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(51.47269458250001, 48.734999999999985), module, BitBusMeterAndFreeze::Panel::Red_Bit1_Status5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(42.05966958250001, 48.734999999999985), module, BitBusMeterAndFreeze::Panel::Red_Bit1_Status4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(32.64656958249999, 48.734999999999985), module, BitBusMeterAndFreeze::Panel::Red_Bit1_Status3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(23.233544582499988, 48.734999999999985), module, BitBusMeterAndFreeze::Panel::Red_Bit1_Status2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(13.820444582499988, 48.734999999999985), module, BitBusMeterAndFreeze::Panel::Red_Bit1_Status1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(14.3535, 346.6866), module, BitBusMeterAndFreeze::Panel::Red_BusIn));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(75.3535, 346.6866), module, BitBusMeterAndFreeze::Panel::Red_BusOut));
}
