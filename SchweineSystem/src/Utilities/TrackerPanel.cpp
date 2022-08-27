#include "Tracker.h"
#include "TrackerPanel.h"

#include <SvinMaster.h>

void Tracker::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Display, "Display");
   configButton(Panel::ModeManual, "ModeManual");

   configInput(Panel::Upload, "Upload");
   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");
   configInput(Panel::Group2_Pass, "Group2_Pass");
   configInput(Panel::Group1_Pass, "Group1_Pass");

   configOutput(Panel::Group2_Output, "Group2_Output");
   configOutput(Panel::Group1_Output, "Group1_Output");

   configPixels(Panel::Pixels_Display, 100, 180, "Display");
}

void TrackerWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/Utilities/Tracker.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(46.10, 228.33), Tracker::Panel::Display);
   makeButton(this, Vec(99.68, 228.33), Tracker::Panel::ModeManual);

   makeInput(this, Vec(95.83, 355.81),  Tracker::Panel::Upload, false);
   makeInput(this, Vec(56.92, 355.83),  Tracker::Panel::Reset, false);
   makeInput(this, Vec(24.17, 355.83),  Tracker::Panel::Clock, false);
   makeInput(this, Vec(24.17, 300.21),  Tracker::Panel::Group2_Pass, true);
   makeInput(this, Vec(24.17, 266.71),  Tracker::Panel::Group1_Pass, true);

   makeOutput(this, Vec(95.83, 300.21), Tracker::Panel::Group2_Output, true);
   makeOutput(this, Vec(95.83, 266.71), Tracker::Panel::Group1_Output, true);

   makeOLED(this, Vec(9.00, 34.00), Tracker::Panel::Pixels_Display, 100, 180);
}

