#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include "SchweineSystemMaster.h"

VCMCReceiver::VCMCReceiver()
   : Module()
{
   setup();
}

VCMCReceiver::~VCMCReceiver()
{
}

void VCMCReceiver::process(const ProcessArgs& args)
{
}

Model* modelVCMCReceiver = SchweineSystem::Master::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");
