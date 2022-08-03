#include "MidiReplay.h"
#include "MidiReplayPanel.h"

#include <SchweineSystemMaster.h>

MidiReplay::MidiReplay()
   : SchweineSystem::Module()
   , displayController(this, Panel::Pixels_Display, 100, 170)
{
   setup();
}
void MidiReplay::process(const ProcessArgs& args)
{
}


// widget

MidiReplayWidget::MidiReplayWidget(MidiReplay* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelMidiReplay = SchweineSystem::Master::the()->addModule<MidiReplay, MidiReplayWidget>("MidiReplay");
