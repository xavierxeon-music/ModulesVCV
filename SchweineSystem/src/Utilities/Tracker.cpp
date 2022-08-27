#include "Tracker.h"
#include "TrackerPanel.h"

#include <SvinMaster.h>

Tracker::Tracker()
   : Svin::Module()
{
   setup();
}

void Tracker::process(const ProcessArgs& args)
{
}


// widget

TrackerWidget::TrackerWidget(Tracker* module)
: Svin::ModuleWidget(module)
{
   setup();
}

Model* modelTracker = Svin::Master::the()->addModule<Tracker, TrackerWidget>("Tracker");
