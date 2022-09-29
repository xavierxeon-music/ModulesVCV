#include "GateKeeper.h"

GateKeeper::GateKeeper()
   : Svin::Module()
{
   setup();
}

void GateKeeper::process(const ProcessArgs& args)
{
}


// widget

GateKeeperWidget::GateKeeperWidget(GateKeeper* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelGateKeeper = Svin::Origin::the()->addModule<GateKeeper, GateKeeperWidget>("GateKeeper");

