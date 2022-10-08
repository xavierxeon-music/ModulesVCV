#include "GrooveMaestro.h"

GrooveMaestro::GrooveMaestro()
   : Svin::Module()
   , Svin::MasterClock::Client()
{
   setup();
}

void GrooveMaestro::process(const ProcessArgs& args)
{
}

// widget

GrooveMaestroWidget::GrooveMaestroWidget(GrooveMaestro* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelGrooveMaestro = Svin::Origin::the()->addModule<GrooveMaestro, GrooveMaestroWidget>("GrooveMaestro");
