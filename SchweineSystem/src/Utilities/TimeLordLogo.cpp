#include "TimeLordLogo.h"
#include "TimeLordLogoPanel.h"

#include <SyMaster.h>

TimeLordLogo::TimeLordLogo()
   : Sy::Module()
{
   setup();
}

void TimeLordLogo::process(const ProcessArgs& args)
{
}


// widget

TimeLordLogoWidget::TimeLordLogoWidget(TimeLordLogo* module)
: Sy::ModuleWidget(module)
{
   setup();
}

Model* modelTimeLordLogo = Sy::Master::the()->addModule<TimeLordLogo, TimeLordLogoWidget>("TimeLordLogo");
