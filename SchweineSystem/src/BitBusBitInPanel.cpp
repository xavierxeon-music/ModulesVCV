#include "BitBusBitIn.h"
#include "BitBusBitInPanel.h"

#include "SchweineSystem.h"

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
   std::string panelPath = asset::plugin(SchweineSystem::the()->instance(), "res/BitBusBitIn.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 291.05475081), module, BitBusBitIn::Panel::BitIn8));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 256.30315081000003), module, BitBusBitIn::Panel::BitIn7));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 186.80035081), module, BitBusBitIn::Panel::BitIn6));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 221.55175081), module, BitBusBitIn::Panel::BitIn5));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 152.04895081), module, BitBusBitIn::Panel::BitIn4));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 117.29755081), module, BitBusBitIn::Panel::BitIn3));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 82.54615081), module, BitBusBitIn::Panel::BitIn2));
   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 47.79475081000001), module, BitBusBitIn::Panel::BitIn1));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(45.35351, 346.6866), module, BitBusBitIn::Panel::Red_BusOut));
}

