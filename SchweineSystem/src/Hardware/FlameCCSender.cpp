#include "FlameCCSender.h"
#include "FlameCCSenderPanel.h"

#include <SvinMaster.h>

FlameCCSender::FlameCCSender()
   : Svin::Module()
{
   setup();
}

void FlameCCSender::process(const ProcessArgs& args)
{
}


// widget

FlameCCSenderWidget::FlameCCSenderWidget(FlameCCSender* module)
: Svin::ModuleWidget(module)
{
   setup();
}

Model* modelFlameCCSender = Svin::Master::the()->addModule<FlameCCSender, FlameCCSenderWidget>("FlameCCSender");
