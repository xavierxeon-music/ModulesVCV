#include "MidiReplay.h"
#include "MidiReplayPanel.h"

#include <SchweineSystemMaster.h>

void MidiReplay::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Display, "Display");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");
   configInput(Panel::Play, "Play");

   configOutput(Panel::Velocity, "Velocity");
   configOutput(Panel::Gate, "Gate");
   configOutput(Panel::Pitch, "Pitch");
   configOutput(Panel::End, "End");

   configPixels(Panel::Pixels_Display, 100, 135, "Display");
}

void MidiReplayWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/MidiReplay.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(73.07, 34.08), MidiReplay::Panel::Display);

   makeLEDButton(this, Vec(35.16, 214.09), MidiReplay::Panel::Loop, MidiReplay::Panel::RGB_Loop);

   makeInput(this, Vec(34.94, 355.83),  MidiReplay::Panel::Reset);
   makeInput(this, Vec(34.94, 309.70),  MidiReplay::Panel::Clock);
   makeInput(this, Vec(34.94, 262.70),  MidiReplay::Panel::Play);

   makeOutput(this, Vec(85.06, 355.83), MidiReplay::Panel::Velocity);
   makeOutput(this, Vec(85.06, 309.01), MidiReplay::Panel::Gate);
   makeOutput(this, Vec(85.06, 262.35), MidiReplay::Panel::Pitch);
   makeOutput(this, Vec(85.06, 215.10), MidiReplay::Panel::End);

   makeOLED(this, Vec(9.00, 45.38), MidiReplay::Panel::Pixels_Display, 100, 135);
}

