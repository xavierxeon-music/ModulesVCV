#include "VCMCReceiver.h"
#include "VCMCReceiverPanel.h"

#include "SchweineSystemLCDDisplay.h"
#include "SchweineSystemMaster.h"

VCMCReceiver::VCMCReceiver()
   : Module()
{
   setup();

   bpm = 223;
}

VCMCReceiver::~VCMCReceiver()
{
}

void VCMCReceiver::process(const ProcessArgs& args)
{
}

VCMCReceiverWidget::VCMCReceiverWidget(VCMCReceiver* module)
   : ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;

   SchweineSystem::LCDDisplay* bpmDisplay = new SchweineSystem::LCDDisplay(module->bpm, 3);
   bpmDisplay->setPosition(90, 297);
   //bpmDisplay->setDigitColor(SchweineSystem::Color{0, 0, 255});

   addChild(bpmDisplay);
}

Model* modelVCMCReceiver = SchweineSystem::Master::the()->addModule<VCMCReceiver, VCMCReceiverWidget>("VCMCReceiver");

