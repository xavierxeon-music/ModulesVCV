#include "Bitify.h"
#include "BitifyPanel.h"

#include "SchweineSystem.h"

void Bitify::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::FlipSwitch8, "FlipSwitch8");
   configButton(Panel::FlipSwitch7, "FlipSwitch7");
   configButton(Panel::FlipSwitch6, "FlipSwitch6");
   configButton(Panel::FlipSwitch5, "FlipSwitch5");
   configButton(Panel::FlipSwitch4, "FlipSwitch4");
   configButton(Panel::FlipSwitch3, "FlipSwitch3");
   configButton(Panel::FlipSwitch2, "FlipSwitch2");
   configButton(Panel::FlipSwitch1, "FlipSwitch1");

   configInput(Panel::AudioIn, "AudioIn");
   configInput(Panel::Hold, "Hold");
   configInput(Panel::BitIn8, "BitIn8");
   configInput(Panel::GateIn8, "GateIn8");
   configInput(Panel::BitIn7, "BitIn7");
   configInput(Panel::GateIn7, "GateIn7");
   configInput(Panel::BitIn6, "BitIn6");
   configInput(Panel::GateIn6, "GateIn6");
   configInput(Panel::BitIn5, "BitIn5");
   configInput(Panel::GateIn5, "GateIn5");
   configInput(Panel::BitIn4, "BitIn4");
   configInput(Panel::GateIn4, "GateIn4");
   configInput(Panel::BitIn3, "BitIn3");
   configInput(Panel::GateIn3, "GateIn3");
   configInput(Panel::BitIn2, "BitIn2");
   configInput(Panel::GateIn2, "GateIn2");
   configInput(Panel::BitIn1, "BitIn1");
   configInput(Panel::GateIn1, "GateIn1");

   configOutput(Panel::AudioOut, "AudioOut");
   configOutput(Panel::BitOut8, "BitOut8");
   configOutput(Panel::BitOut7, "BitOut7");
   configOutput(Panel::BitOut6, "BitOut6");
   configOutput(Panel::BitOut5, "BitOut5");
   configOutput(Panel::BitOut4, "BitOut4");
   configOutput(Panel::BitOut3, "BitOut3");
   configOutput(Panel::BitOut2, "BitOut2");
   configOutput(Panel::BitOut1, "BitOut1");
}

BitifyWidget::BitifyWidget(Bitify* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::the()->instance(), "res/Bitify.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(34.89121546371889, 293.14856081), module, Bitify::Panel::FlipSwitch8, Bitify::Panel::Red_FlipSwitch8));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(34.89121546371889, 257.96696081), module, Bitify::Panel::FlipSwitch7, Bitify::Panel::Red_FlipSwitch7));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(34.89121546371889, 222.69356081), module, Bitify::Panel::FlipSwitch6, Bitify::Panel::Red_FlipSwitch6));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(34.86793004951888, 187.48976081), module, Bitify::Panel::FlipSwitch5, Bitify::Panel::Red_FlipSwitch5));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(34.84474457271888, 152.23936081), module, Bitify::Panel::FlipSwitch4, Bitify::Panel::Red_FlipSwitch4));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(34.89121546371889, 117.01206081), module, Bitify::Panel::FlipSwitch3, Bitify::Panel::Red_FlipSwitch3));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(34.89121546371889, 81.83126081), module, Bitify::Panel::FlipSwitch2, Bitify::Panel::Red_FlipSwitch2));
   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(34.89121546371889, 46.28986081), module, Bitify::Panel::FlipSwitch1, Bitify::Panel::Red_FlipSwitch1));

   addInput(createInputCentered<PJ301MPort>(Vec(152.702544858, 330.6573508099999), module, Bitify::Panel::AudioIn));
   addInput(createInputCentered<PJ301MPort>(Vec(57.194044858000005, 330.65735080999997), module, Bitify::Panel::Hold));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 292.74875081), module, Bitify::Panel::BitIn8));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 293.19496081), module, Bitify::Panel::GateIn8));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 257.52075081), module, Bitify::Panel::BitIn7));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 257.96696081), module, Bitify::Panel::GateIn7));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 222.29375081), module, Bitify::Panel::BitIn6));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 222.73996081), module, Bitify::Panel::GateIn6));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 187.06675080999997), module, Bitify::Panel::BitIn5));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 187.51296080999998), module, Bitify::Panel::GateIn5));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 151.83955081), module, Bitify::Panel::BitIn4));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 152.28576081), module, Bitify::Panel::GateIn4));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 116.61225080999999), module, Bitify::Panel::BitIn3));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 117.05846081), module, Bitify::Panel::GateIn3));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 81.38505081), module, Bitify::Panel::BitIn2));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 81.83126081), module, Bitify::Panel::GateIn2));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 46.15785080999999), module, Bitify::Panel::BitIn1));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 46.60406081), module, Bitify::Panel::GateIn1));

   addOutput(createOutputCentered<PJ301MPort>(Vec(185.826544858, 330.6573508099999), module, Bitify::Panel::AudioOut));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 293.19505081), module, Bitify::Panel::BitOut8));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 257.96705081), module, Bitify::Panel::BitOut7));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 222.74005081), module, Bitify::Panel::BitOut6));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 187.51305080999998), module, Bitify::Panel::BitOut5));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 152.28585081), module, Bitify::Panel::BitOut4));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 117.05855081), module, Bitify::Panel::BitOut3));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 81.83135081), module, Bitify::Panel::BitOut2));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 46.60415081), module, Bitify::Panel::BitOut1));
}

