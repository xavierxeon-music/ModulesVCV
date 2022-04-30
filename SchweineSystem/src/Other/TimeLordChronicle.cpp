#include "TimeLordChronicle.h"
#include "TimeLordChroniclePanel.h"

#include <SchweineSystemMaster.h>

TimeLordChronicle::TimeLordChronicle()
   : SchweineSystem::Module()
{
   setup();
}

void TimeLordChronicle::process(const ProcessArgs& args)
{
}

TimeLordChronicleWidget::TimeLordChronicleWidget(TimeLordChronicle* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelTimeLordChronicle = SchweineSystem::Master::the()->addModule<TimeLordChronicle, TimeLordChronicleWidget>("TimeLordChronicle");
