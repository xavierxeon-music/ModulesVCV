#include "MidiReplay.h"
#include "MidiReplayPanel.h"

#include <SchweineSystemMaster.h>

void MidiReplay::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");

   configOutput(Panel::Velocity, "Velocity");
   configOutput(Panel::Gate, "Gate");
   configOutput(Panel::Pitch, "Pitch");

   configPixels(Panel::Pixels_Display, 100, 170, "Display");
}

void MidiReplayWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/MidiReplay.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(34.94, 355.83),  MidiReplay::Panel::Reset);
   makeInput(this, Vec(34.94, 306.70),  MidiReplay::Panel::Clock);

   makeOutput(this, Vec(85.06, 355.83), MidiReplay::Panel::Velocity);
   makeOutput(this, Vec(85.06, 306.70), MidiReplay::Panel::Gate);
   makeOutput(this, Vec(85.06, 258.10), MidiReplay::Panel::Pitch);

   makeOLED(this, Vec(9.00, 38.38), MidiReplay::Panel::Pixels_Display, 100, 170);
}

