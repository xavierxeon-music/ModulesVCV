#include "BitBusMeterAndFreeze.h"
#include "BitBusMeterAndFreezePanel.h"

#include "SchweineSystem.h"

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
   std::string panelPath = asset::plugin(SchweineSystem::the()->instance(), "res/BitBusMeterAndFreeze.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(55.80498966800001, 244.94665081), module, BitBusMeterAndFreeze::Panel::FlipSample, BitBusMeterAndFreeze::Panel::Red_FlipSample));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(55.80498966800001, 145.95655081), module, BitBusMeterAndFreeze::Panel::FlipFreeze, BitBusMeterAndFreeze::Panel::Red_FlipFreeze));

   addInput(createInputCentered<PJ301MPort>(Vec(55.80498966800001, 209.14595081), module, BitBusMeterAndFreeze::Panel::GateSample));
   addInput(createInputCentered<PJ301MPort>(Vec(55.80498966800001, 110.39405081), module, BitBusMeterAndFreeze::Panel::GateFreeze));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(18.615399999999994, 291.227), module, BitBusMeterAndFreeze::Panel::Red_Bit8));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(18.615399999999994, 257.587), module, BitBusMeterAndFreeze::Panel::Red_Bit7));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(18.615399999999994, 222.219), module, BitBusMeterAndFreeze::Panel::Red_Bit6));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(18.615399999999994, 186.912), module, BitBusMeterAndFreeze::Panel::Red_Bit5));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(18.615399999999994, 153.46599999999998), module, BitBusMeterAndFreeze::Panel::Red_Bit4));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(18.615399999999994, 118.69000000000003), module, BitBusMeterAndFreeze::Panel::Red_Bit3));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(18.615399999999994, 84.393), module, BitBusMeterAndFreeze::Panel::Red_Bit2));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(18.615399999999994, 48.734999999999985), module, BitBusMeterAndFreeze::Panel::Red_Bit1));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(14.3535, 346.6866), module, BitBusMeterAndFreeze::Panel::Red_BusIn));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(75.3535, 346.6866), module, BitBusMeterAndFreeze::Panel::Red_BusOut));
}

