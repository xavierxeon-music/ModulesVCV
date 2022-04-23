#include "DoepferQuad.h"
#include "DoepferQuadPanel.h"

#include <SchweineSystemMaster.h>

void DoepferQuad::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Channel4_In3, "Channel4_In3");
   configInput(Panel::Channel4_In2, "Channel4_In2");
   configInput(Panel::Channel4_In1, "Channel4_In1");
   configInput(Panel::Channel3_In3, "Channel3_In3");
   configInput(Panel::Channel3_In2, "Channel3_In2");
   configInput(Panel::Channel3_In1, "Channel3_In1");
   configInput(Panel::Channel2_In3, "Channel2_In3");
   configInput(Panel::Channel2_In2, "Channel2_In2");
   configInput(Panel::Channel2_In1, "Channel2_In1");
   configInput(Panel::Channel1_In3, "Channel1_In3");
   configInput(Panel::Channel1_In2, "Channel1_In2");
   configInput(Panel::Channel1_In1, "Channel1_In1");
}

SvgPanel* DoepferQuadWidget::setup(DoepferQuad* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/DoepferQuad.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(57.76700266799999, 359.48755080999996), module, DoepferQuad::Panel::Connect, DoepferQuad::Panel::Red_Connect));

   addInput(createInputCentered<PJ301MPort>(Vec(65.82681485799999, 328.13175080999997), module, DoepferQuad::Panel::Channel4_In3));
   addInput(createInputCentered<PJ301MPort>(Vec(65.82681485799999, 295.73575081), module, DoepferQuad::Panel::Channel4_In2));
   addInput(createInputCentered<PJ301MPort>(Vec(65.82681485799999, 263.34005081), module, DoepferQuad::Panel::Channel4_In1));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244857999997, 328.07175081), module, DoepferQuad::Panel::Channel3_In3));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244857999997, 295.67575080999995), module, DoepferQuad::Panel::Channel3_In2));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244857999997, 263.28005081), module, DoepferQuad::Panel::Channel3_In1));
   addInput(createInputCentered<PJ301MPort>(Vec(65.82681485799999, 217.61455081), module, DoepferQuad::Panel::Channel2_In3));
   addInput(createInputCentered<PJ301MPort>(Vec(65.82681485799999, 185.21855080999998), module, DoepferQuad::Panel::Channel2_In2));
   addInput(createInputCentered<PJ301MPort>(Vec(65.82681485799999, 152.82285081), module, DoepferQuad::Panel::Channel2_In1));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244857999997, 217.55455081), module, DoepferQuad::Panel::Channel1_In3));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244857999997, 185.15855080999998), module, DoepferQuad::Panel::Channel1_In2));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244857999997, 152.76285081), module, DoepferQuad::Panel::Channel1_In1));

   return mainPanel;
}

