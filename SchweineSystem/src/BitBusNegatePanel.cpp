#include "BitBusNegate.h"
#include "BitBusNegatePanel.h"

#include "SchweineSystem.h"

void BitBusNegate::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Latch8, "Latch8");
   configButton(Panel::Latch7, "Latch7");
   configButton(Panel::Latch6, "Latch6");
   configButton(Panel::Latch5, "Latch5");
   configButton(Panel::Latch4, "Latch4");
   configButton(Panel::Latch3, "Latch3");
   configButton(Panel::Latch2, "Latch2");
   configButton(Panel::Latch1, "Latch1");

   configInput(Panel::GateIn8, "GateIn8");
   configInput(Panel::GateIn7, "GateIn7");
   configInput(Panel::GateIn6, "GateIn6");
   configInput(Panel::GateIn5, "GateIn5");
   configInput(Panel::GateIn4, "GateIn4");
   configInput(Panel::GateIn3, "GateIn3");
   configInput(Panel::GateIn2, "GateIn2");
   configInput(Panel::GateIn1, "GateIn1");

}

BitBusNegateWidget::BitBusNegateWidget(BitBusNegate* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::the()->instance(), "res/BitBusNegate.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 291.18175081000004), module, BitBusNegate::Panel::Latch8, BitBusNegate::Panel::Red_Latch8));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 257.43015081), module, BitBusNegate::Panel::Latch7, BitBusNegate::Panel::Red_Latch7));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 222.14545081), module, BitBusNegate::Panel::Latch6, BitBusNegate::Panel::Red_Latch6));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 186.65985081000002), module, BitBusNegate::Panel::Latch5, BitBusNegate::Panel::Red_Latch5));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 153.30825081), module, BitBusNegate::Panel::Latch4, BitBusNegate::Panel::Red_Latch4));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 118.53265081), module, BitBusNegate::Panel::Latch3, BitBusNegate::Panel::Red_Latch3));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 84.17175081), module, BitBusNegate::Panel::Latch2, BitBusNegate::Panel::Red_Latch2));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(29.231120132499996, 48.43375081000001), module, BitBusNegate::Panel::Latch1, BitBusNegate::Panel::Red_Latch1));

   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 291.49575081), module, BitBusNegate::Panel::GateIn8));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 257.74435081), module, BitBusNegate::Panel::GateIn7));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 222.45965081), module, BitBusNegate::Panel::GateIn6));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 186.97405081), module, BitBusNegate::Panel::GateIn5));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 153.62245081), module, BitBusNegate::Panel::GateIn4));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 118.84695081000001), module, BitBusNegate::Panel::GateIn3));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 84.48595081), module, BitBusNegate::Panel::GateIn2));
   addInput(createInputCentered<PJ301MPort>(Vec(60.769370132500015, 48.748750810000004), module, BitBusNegate::Panel::GateIn1));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(14.3535, 346.6866), module, BitBusNegate::Panel::Red_BusIn));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(75.3535, 346.6866), module, BitBusNegate::Panel::Red_BusOut));
}

