#include "BitBusCVInPanel.h"
#include "BitBusCVIn.h"

#include "SchweineSystemMaster.h"

void BitBusCVIn::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::CVIn, "CVIn");
}

BitBusCVInWidget::BitBusCVInWidget(BitBusCVIn* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusCVIn.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addInput(createInputCentered<PJ301MPort>(Vec(24.173244858000004, 169.98075181000002), module, BitBusCVIn::Panel::CVIn));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(45.35351, 346.6866), module, BitBusCVIn::Panel::Red_BusOut));
}
