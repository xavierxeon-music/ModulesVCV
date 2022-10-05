#include "DrumTrigger.h"

DrumTrigger::DrumTrigger()
   : Svin::Module()
{
   setup();
}

void DrumTrigger::process(const ProcessArgs& args)
{
}


// widget

DrumTriggerWidget::DrumTriggerWidget(DrumTrigger* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelDrumTrigger = Svin::Origin::the()->addModule<DrumTrigger, DrumTriggerWidget>("DrumTrigger");

