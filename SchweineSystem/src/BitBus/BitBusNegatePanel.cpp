#include "BitBusNegate.h"
#include "BitBusNegatePanel.h"

#include "SchweineSystem.h"

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

BitBusNegateWidget::BitBusNegateWidget(BitBusNegate* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::the()->instance(), "res/BitBusNegate.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 291.18175081000004), module, BitBusNegate::Panel::Bit8_Latch, BitBusNegate::Panel::Red_Bit8_Latch));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 257.43015081), module, BitBusNegate::Panel::Bit7_Latch, BitBusNegate::Panel::Red_Bit7_Latch));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 222.14545081), module, BitBusNegate::Panel::Bit6_Latch, BitBusNegate::Panel::Red_Bit6_Latch));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 186.65985081000002), module, BitBusNegate::Panel::Bit5_Latch, BitBusNegate::Panel::Red_Bit5_Latch));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 153.30825081), module, BitBusNegate::Panel::Bit4_Latch, BitBusNegate::Panel::Red_Bit4_Latch));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 118.53265081), module, BitBusNegate::Panel::Bit3_Latch, BitBusNegate::Panel::Red_Bit3_Latch));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 84.17175081), module, BitBusNegate::Panel::Bit2_Latch, BitBusNegate::Panel::Red_Bit2_Latch));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 48.43375081000001), module, BitBusNegate::Panel::Bit1_Latch, BitBusNegate::Panel::Red_Bit1_Latch));

   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 291.49575081), module, BitBusNegate::Panel::Bit8_GateIn));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 257.74435081), module, BitBusNegate::Panel::Bit7_GateIn));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 222.45965081), module, BitBusNegate::Panel::Bit6_GateIn));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 186.97405081), module, BitBusNegate::Panel::Bit5_GateIn));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 153.62245081), module, BitBusNegate::Panel::Bit4_GateIn));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 118.84695081000001), module, BitBusNegate::Panel::Bit3_GateIn));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 84.48595081), module, BitBusNegate::Panel::Bit2_GateIn));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 48.748750810000004), module, BitBusNegate::Panel::Bit1_GateIn));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(14.3535, 346.6866), module, BitBusNegate::Panel::Red_BusIn));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(75.3535, 346.6866), module, BitBusNegate::Panel::Red_BusOut));
}

