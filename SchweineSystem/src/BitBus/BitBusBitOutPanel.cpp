#include "BitBusBitOutPanel.h"
#include "BitBusBitOut.h"

#include "SchweineSystemMaster.h"

void BitBusBitOut::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configOutput(Panel::BitOut8, "BitOut8");
   configOutput(Panel::BitOut7, "BitOut7");
   configOutput(Panel::BitOut6, "BitOut6");
   configOutput(Panel::BitOut5, "BitOut5");
   configOutput(Panel::BitOut4, "BitOut4");
   configOutput(Panel::BitOut3, "BitOut3");
   configOutput(Panel::BitOut2, "BitOut2");
   configOutput(Panel::BitOut1, "BitOut1");
}

BitBusBitOutWidget::BitBusBitOutWidget(BitBusBitOut* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusBitOut.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addOutput(createOutputCentered<PJ301MPort>(Vec(30.000044857999995, 291.61075081), module, BitBusBitOut::Panel::BitOut8));
   addOutput(createOutputCentered<PJ301MPort>(Vec(30.000044857999995, 256.85925081), module, BitBusBitOut::Panel::BitOut7));
   addOutput(createOutputCentered<PJ301MPort>(Vec(30.000044857999995, 187.35645081), module, BitBusBitOut::Panel::BitOut6));
   addOutput(createOutputCentered<PJ301MPort>(Vec(30.000044857999995, 222.10785081), module, BitBusBitOut::Panel::BitOut5));
   addOutput(createOutputCentered<PJ301MPort>(Vec(30.000044857999995, 152.60505081), module, BitBusBitOut::Panel::BitOut4));
   addOutput(createOutputCentered<PJ301MPort>(Vec(30.000044857999995, 117.85365081), module, BitBusBitOut::Panel::BitOut3));
   addOutput(createOutputCentered<PJ301MPort>(Vec(30.000044857999995, 83.10225081), module, BitBusBitOut::Panel::BitOut2));
   addOutput(createOutputCentered<PJ301MPort>(Vec(30.000044857999995, 48.35075081000001), module, BitBusBitOut::Panel::BitOut1));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(14.3535, 346.6866), module, BitBusBitOut::Panel::Red_BusIn));
   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(46.35351, 346.6866), module, BitBusBitOut::Panel::Red_BusOut));
}
