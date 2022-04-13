#include "Bitify.h"
#include "BitifyData.h"

#include "Schweinesystem.h"

void Bitify::setup()
{
   config(Data::PARAMS_LEN, Data::INPUTS_LEN, Data::OUTPUTS_LEN, Data::LIGHTS_LEN);

   configButton(Data::FlipSwitch8, "FlipSwitch8");
   configButton(Data::FlipSwitch7, "FlipSwitch7");
   configButton(Data::FlipSwitch6, "FlipSwitch6");
   configButton(Data::FlipSwitch5, "FlipSwitch5");
   configButton(Data::FlipSwitch4, "FlipSwitch4");
   configButton(Data::FlipSwitch3, "FlipSwitch3");
   configButton(Data::FlipSwitch2, "FlipSwitch2");
   configButton(Data::FlipSwitch1, "FlipSwitch1");

   configInput(Data::AudioIn, "AudioIn");
   configInput(Data::Hold, "Hold");
   configInput(Data::BitIn8, "BitIn8");
   configInput(Data::GateIn8, "GateIn8");
   configInput(Data::BitIn7, "BitIn7");
   configInput(Data::GateIn7, "GateIn7");
   configInput(Data::BitIn6, "BitIn6");
   configInput(Data::GateIn6, "GateIn6");
   configInput(Data::BitIn5, "BitIn5");
   configInput(Data::GateIn5, "GateIn5");
   configInput(Data::BitIn4, "BitIn4");
   configInput(Data::GateIn4, "GateIn4");
   configInput(Data::BitIn3, "BitIn3");
   configInput(Data::GateIn3, "GateIn3");
   configInput(Data::BitIn2, "BitIn2");
   configInput(Data::GateIn2, "GateIn2");
   configInput(Data::BitIn1, "BitIn1");
   configInput(Data::GateIn1, "GateIn1");

   configOutput(Data::AudioOut, "AudioOut");
   configOutput(Data::BitOut8, "BitOut8");
   configOutput(Data::BitOut7, "BitOut7");
   configOutput(Data::BitOut6, "BitOut6");
   configOutput(Data::BitOut5, "BitOut5");
   configOutput(Data::BitOut4, "BitOut4");
   configOutput(Data::BitOut3, "BitOut3");
   configOutput(Data::BitOut2, "BitOut2");
   configOutput(Data::BitOut1, "BitOut1");
}

BitifyWidget::BitifyWidget(Bitify* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(Schweinesystem::instance(), "res/Bitify.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(Vec(34.89121546371889, 293.14856081), module, Bitify::Data::FlipSwitch8, Bitify::Data::Light_FlipSwitch8));
   addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(Vec(34.89121546371889, 257.96696081), module, Bitify::Data::FlipSwitch7, Bitify::Data::Light_FlipSwitch7));
   addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(Vec(34.89121546371889, 222.69356081), module, Bitify::Data::FlipSwitch6, Bitify::Data::Light_FlipSwitch6));
   addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(Vec(34.86793004951888, 187.48976081), module, Bitify::Data::FlipSwitch5, Bitify::Data::Light_FlipSwitch5));
   addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(Vec(34.84474457271888, 152.23936081), module, Bitify::Data::FlipSwitch4, Bitify::Data::Light_FlipSwitch4));
   addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(Vec(34.89121546371889, 117.01206081), module, Bitify::Data::FlipSwitch3, Bitify::Data::Light_FlipSwitch3));
   addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(Vec(34.89121546371889, 81.83126081), module, Bitify::Data::FlipSwitch2, Bitify::Data::Light_FlipSwitch2));
   addParam(createLightParamCentered<VCVLightBezel<WhiteLight>>(Vec(34.89121546371889, 46.28986081), module, Bitify::Data::FlipSwitch1, Bitify::Data::Light_FlipSwitch1));

   addInput(createInputCentered<PJ301MPort>(Vec(152.702544858, 330.6573508099999), module, Bitify::Data::AudioIn));
   addInput(createInputCentered<PJ301MPort>(Vec(57.194044858000005, 330.65735080999997), module, Bitify::Data::Hold));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 292.74875081), module, Bitify::Data::BitIn8));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 293.19496081), module, Bitify::Data::GateIn8));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 257.52075081), module, Bitify::Data::BitIn7));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 257.96696081), module, Bitify::Data::GateIn7));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 222.29375081), module, Bitify::Data::BitIn6));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 222.73996081), module, Bitify::Data::GateIn6));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 187.06675080999997), module, Bitify::Data::BitIn5));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 187.51296080999998), module, Bitify::Data::GateIn5));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 151.83955081), module, Bitify::Data::BitIn4));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 152.28576081), module, Bitify::Data::GateIn4));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 116.61225080999999), module, Bitify::Data::BitIn3));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 117.05846081), module, Bitify::Data::GateIn3));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 81.38505081), module, Bitify::Data::BitIn2));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 81.83126081), module, Bitify::Data::GateIn2));
   addInput(createInputCentered<PJ301MPort>(Vec(181.83527086511887, 46.15785080999999), module, Bitify::Data::BitIn1));
   addInput(createInputCentered<PJ301MPort>(Vec(66.42916034351889, 46.60406081), module, Bitify::Data::GateIn1));

   addOutput(createOutputCentered<PJ301MPort>(Vec(185.826544858, 330.6573508099999), module, Bitify::Data::AudioOut));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 293.19505081), module, Bitify::Data::BitOut8));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 257.96705081), module, Bitify::Data::BitOut7));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 222.74005081), module, Bitify::Data::BitOut6));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 187.51305080999998), module, Bitify::Data::BitOut5));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 152.28585081), module, Bitify::Data::BitOut4));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 117.05855081), module, Bitify::Data::BitOut3));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 81.83135081), module, Bitify::Data::BitOut2));
   addOutput(createOutputCentered<PJ301MPort>(Vec(121.16427469911886, 46.60415081), module, Bitify::Data::BitOut1));
}
