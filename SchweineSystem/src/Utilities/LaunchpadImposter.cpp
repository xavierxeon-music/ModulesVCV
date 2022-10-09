#include "LaunchpadImposter.h"

LaunchpadImposter::LaunchpadImposter()
   : Svin::Module()
{
   setup();
}

void LaunchpadImposter::process(const ProcessArgs& args)
{
}


// widget

LaunchpadImposterWidget::LaunchpadImposterWidget(LaunchpadImposter* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelLaunchpadImposter = Svin::Origin::the()->addModule<LaunchpadImposter, LaunchpadImposterWidget>("LaunchpadImposter");

