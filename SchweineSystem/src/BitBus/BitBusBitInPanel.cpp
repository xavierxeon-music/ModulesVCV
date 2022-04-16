#include "BitBusBitInPanel.h"
#include "BitBusBitIn.h"

#include "SchweineSystemMaster.h"

void BitBusBitIn::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::BitIn8, "BitIn8");
   configInput(Panel::BitIn7, "BitIn7");
   configInput(Panel::BitIn6, "BitIn6");
   configInput(Panel::BitIn5, "BitIn5");
   configInput(Panel::BitIn4, "BitIn4");
   configInput(Panel::BitIn3, "BitIn3");
   configInput(Panel::BitIn2, "BitIn2");
   configInput(Panel::BitIn1, "BitIn1");
}

BitBusBitInWidget::BitBusBitInWidget(BitBusBitIn* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusBitIn.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addInput(createInputCentered<PJ301MPort>(Vec(30.000044857999995, 291.61075081), module, BitBusBitIn::Panel::BitIn8));
   addInput(createInputCentered<PJ301MPort>(Vec(30.000044857999995, 256.85925081), module, BitBusBitIn::Panel::BitIn7));
   addInput(createInputCentered<PJ301MPort>(Vec(30.000044857999995, 187.35645081), module, BitBusBitIn::Panel::BitIn6));
   addInput(createInputCentered<PJ301MPort>(Vec(30.000044857999995, 222.10785081), module, BitBusBitIn::Panel::BitIn5));
   addInput(createInputCentered<PJ301MPort>(Vec(30.000044857999995, 152.60505081), module, BitBusBitIn::Panel::BitIn4));
   addInput(createInputCentered<PJ301MPort>(Vec(30.000044857999995, 117.85365081), module, BitBusBitIn::Panel::BitIn3));
   addInput(createInputCentered<PJ301MPort>(Vec(30.000044857999995, 83.10225081), module, BitBusBitIn::Panel::BitIn2));
   addInput(createInputCentered<PJ301MPort>(Vec(30.000044857999995, 48.35075081000001), module, BitBusBitIn::Panel::BitIn1));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(45.35351, 346.6866), module, BitBusBitIn::Panel::Red_BusOut));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(14.3535, 346.6866), module, BitBusBitIn::Panel::Red_BusIn));
}
