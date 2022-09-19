#include "Nosferatu.h"

Nosferatu::Nosferatu()
   : Svin::Module()
{
   setup();
}

void Nosferatu::process(const ProcessArgs& args)
{
}


// widget

NosferatuWidget::NosferatuWidget(Nosferatu* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// creete module
Model* modelNosferatu = Svin::Origin::the()->addModule<Nosferatu, NosferatuWidget>("Nosferatu");

