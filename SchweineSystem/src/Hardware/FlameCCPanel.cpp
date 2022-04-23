#include "FlameCC.h"
#include "FlameCCPanel.h"

#include <SchweineSystemMaster.h>

void FlameCC::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Row8_InB, "Row8_InB");
   configInput(Panel::Row8_InA, "Row8_InA");
   configInput(Panel::Row7_InB, "Row7_InB");
   configInput(Panel::Row7_InA, "Row7_InA");
   configInput(Panel::Row6_InB, "Row6_InB");
   configInput(Panel::Row6_InA, "Row6_InA");
   configInput(Panel::Row5_InB, "Row5_InB");
   configInput(Panel::Row5_InA, "Row5_InA");
   configInput(Panel::Row4_InB, "Row4_InB");
   configInput(Panel::Row4_InA, "Row4_InA");
   configInput(Panel::Row3_InB, "Row3_InB");
   configInput(Panel::Row3_InA, "Row3_InA");
   configInput(Panel::Row2_InB, "Row2_InB");
   configInput(Panel::Row2_InA, "Row2_InA");
   configInput(Panel::Row1_InB, "Row1_InB");
   configInput(Panel::Row1_InA, "Row1_InA");
}

SvgPanel* FlameCCWidget::setup(FlameCC* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/FlameCC.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addParam(createLightParamCentered<VCVLightBezel<RedGreenBlueLight>>(Vec(57.76700266799999, 359.48755080999996), module, FlameCC::Panel::Connect, FlameCC::Panel::Red_Connect));

   addInput(createInputCentered<PJ301MPort>(Vec(63.826944858000005, 327.95305081), module, FlameCC::Panel::Row8_InB));
   addInput(createInputCentered<PJ301MPort>(Vec(26.172944858000008, 327.87905081), module, FlameCC::Panel::Row8_InA));
   addInput(createInputCentered<PJ301MPort>(Vec(63.826944858000005, 290.65735080999997), module, FlameCC::Panel::Row7_InB));
   addInput(createInputCentered<PJ301MPort>(Vec(26.172944858000008, 290.58335081), module, FlameCC::Panel::Row7_InA));
   addInput(createInputCentered<PJ301MPort>(Vec(63.826944858000005, 253.36165080999996), module, FlameCC::Panel::Row6_InB));
   addInput(createInputCentered<PJ301MPort>(Vec(26.172944858000008, 253.28765081), module, FlameCC::Panel::Row6_InA));
   addInput(createInputCentered<PJ301MPort>(Vec(63.826944858000005, 216.06575080999994), module, FlameCC::Panel::Row5_InB));
   addInput(createInputCentered<PJ301MPort>(Vec(26.172944858000008, 215.99175080999998), module, FlameCC::Panel::Row5_InA));
   addInput(createInputCentered<PJ301MPort>(Vec(63.826944858000005, 178.76975080999995), module, FlameCC::Panel::Row4_InB));
   addInput(createInputCentered<PJ301MPort>(Vec(26.172944858000008, 178.69575081), module, FlameCC::Panel::Row4_InA));
   addInput(createInputCentered<PJ301MPort>(Vec(63.826944858000005, 141.47475080999996), module, FlameCC::Panel::Row3_InB));
   addInput(createInputCentered<PJ301MPort>(Vec(26.172944858000008, 141.40075081), module, FlameCC::Panel::Row3_InA));
   addInput(createInputCentered<PJ301MPort>(Vec(63.826944858000005, 104.17875080999997), module, FlameCC::Panel::Row2_InB));
   addInput(createInputCentered<PJ301MPort>(Vec(26.172944858000008, 104.10475081000001), module, FlameCC::Panel::Row2_InA));
   addInput(createInputCentered<PJ301MPort>(Vec(63.826944858000005, 66.88275080999995), module, FlameCC::Panel::Row1_InB));
   addInput(createInputCentered<PJ301MPort>(Vec(26.172944858000008, 66.80875080999999), module, FlameCC::Panel::Row1_InA));

   return mainPanel;
}

