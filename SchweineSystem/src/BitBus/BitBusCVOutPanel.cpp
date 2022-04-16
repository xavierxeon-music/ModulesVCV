#include "BitBusCVOutPanel.h"
#include "BitBusCVOut.h"

#include "SchweineSystemMaster.h"

void BitBusCVOut::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configOutput(Panel::CVOut, "CVOut");
}

BitBusCVOutWidget::BitBusCVOutWidget(BitBusCVOut* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BitBusCVOut.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   addOutput(createOutputCentered<PJ301MPort>(Vec(35.826544858000005, 169.98075181000002), module, BitBusCVOut::Panel::CVOut));

   addChild(createLightCentered<MediumLight<RedGreenBlueLight>>(Vec(14.3535, 346.6866), module, BitBusCVOut::Panel::Red_BusIn));
}
