#include "MidiCV.h"
#include "MidiCVPanel.h"

#include <SyMaster.h>

void MidiCV::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configOutput(Panel::Velocity, "Velocity");
   configOutput(Panel::Gate, "Gate");
   configOutput(Panel::Pitch, "Pitch");
}

void MidiCVWidget::setup()
{
   std::string panelPath = asset::plugin(Sy::Master::the()->instance(), "res/Utilities/MidiCV.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeOutput(this, Vec(30.00, 309.00), MidiCV::Panel::Velocity, true);
   makeOutput(this, Vec(30.00, 262.18), MidiCV::Panel::Gate, true);
   makeOutput(this, Vec(30.00, 215.52), MidiCV::Panel::Pitch, true);
}

