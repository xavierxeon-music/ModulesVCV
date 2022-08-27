#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include <SvinMaster.h>

VCMCReceiver::VCMCReceiver()
   : Svin::Module()
{
   setup();
}

void VCMCReceiver::process(const ProcessArgs& args)
{
}


// widget

VCMCReceiverWidget::VCMCReceiverWidget(VCMCReceiver* module)
: Svin::ModuleWidget(module)
{
   setup();
}

Model* modelVCMCReceiver = Svin::Master::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");
