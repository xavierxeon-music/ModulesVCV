#include "Mingle.h"

Mingle::Mingle()
   : Svin::Module()
{
   setup();
}

void Mingle::process(const ProcessArgs& args)
{
}


// widget

MingleWidget::MingleWidget(Mingle* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelMingle = Svin::Origin::the()->addModule<Mingle, MingleWidget>("Mingle");

