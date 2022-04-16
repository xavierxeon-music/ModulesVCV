#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include "SchweineSystemMaster.h"

void VCMCReceiver::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

VCMCReceiverWidget::VCMCReceiverWidget(VCMCReceiver* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/VCMCReceiver.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);
}

