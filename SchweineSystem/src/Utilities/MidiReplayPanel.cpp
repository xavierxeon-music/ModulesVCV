#include "MidiReplay.h"
#include "MidiReplayPanel.h"

#include <SchweineSystemMaster.h>

void MidiReplay::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Edit_Right, "Edit_Right");
   configButton(Panel::Edit_Left, "Edit_Left");
   configButton(Panel::Edit_Down, "Edit_Down");
   configButton(Panel::Edit_Up, "Edit_Up");
   configButton(Panel::Page, "Page");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");
   configInput(Panel::Play, "Play");

   configOutput(Panel::End, "End");

   configPixels(Panel::Pixels_Display, 100, 135, "Display");
}

void MidiReplayWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/MidiReplay.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(103.18, 51.37), MidiReplay::Panel::Edit_Right);
   makeButton(this, Vec(76.99, 51.37), MidiReplay::Panel::Edit_Left);
   makeButton(this, Vec(90.09, 63.16), MidiReplay::Panel::Edit_Down);
   makeButton(this, Vec(90.09, 39.59), MidiReplay::Panel::Edit_Up);
   makeButton(this, Vec(36.80, 51.38), MidiReplay::Panel::Page);

   makeLEDButton(this, Vec(84.33, 261.51), MidiReplay::Panel::Loop, MidiReplay::Panel::RGB_Loop);

   makeInput(this, Vec(34.94, 355.83),  MidiReplay::Panel::Reset);
   makeInput(this, Vec(34.94, 309.70),  MidiReplay::Panel::Clock);
   makeInput(this, Vec(34.94, 262.70),  MidiReplay::Panel::Play);

   makeOutput(this, Vec(84.33, 309.97), MidiReplay::Panel::End);

   makeOLED(this, Vec(9.00, 80.91), MidiReplay::Panel::Pixels_Display, 100, 135);
}

