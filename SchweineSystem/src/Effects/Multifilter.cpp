#include "Multifilter.h"
#include "MultifilterPanel.h"

#include <SvinOrigin.h>

Multifilter::Multifilter()
   : Svin::Module()
{
   setup();
}

void Multifilter::process(const ProcessArgs& args)
{
}


// widget

MultifilterWidget::MultifilterWidget(Multifilter* module)
: Svin::ModuleWidget(module)
{
   setup();
}

Model* modelMultifilter = Svin::Origin::the()->addModule<Multifilter, MultifilterWidget>("Multifilter");
