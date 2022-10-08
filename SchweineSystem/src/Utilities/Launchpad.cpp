#include "Launchpad.h"

Launchpad::Launchpad()
   : Svin::Module()
{
   setup();
}

void Launchpad::process(const ProcessArgs& args)
{
}


// widget

LaunchpadWidget::LaunchpadWidget(Launchpad* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelLaunchpad = Svin::Origin::the()->addModule<Launchpad, LaunchpadWidget>("Launchpad");

