#include "Tracker.h"
#include "TrackerPanel.h"

#include <SvinMaster.h>

void Tracker::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::ModeManual, "ModeManual");
   configButton(Panel::Display, "Display");

   configInput(Panel::Upload, "Upload");
   configInput(Panel::ModeCV, "ModeCV");
   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");
   configInput(Panel::Channel2_Pass, "Channel2_Pass");
   configInput(Panel::Channel1_Pass, "Channel1_Pass");

   configOutput(Panel::Channel2_Output, "Channel2_Output");
   configOutput(Panel::Channel1_Output, "Channel1_Output");

   configPixels(Panel::Pixels_Display, 60, 120, "Display");
}

void TrackerWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/Utilities/Tracker.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(31.44, 276.06), Tracker::Panel::ModeManual);
   makeButton(this, Vec(53.91, 35.70), Tracker::Panel::Display);

   makeInput(this, Vec(114.00, 292.55),  Tracker::Panel::Upload, false);
   makeInput(this, Vec(30.21, 305.42),  Tracker::Panel::ModeCV, false);
   makeInput(this, Vec(65.58, 355.83),  Tracker::Panel::Reset, false);
   makeInput(this, Vec(31.38, 355.48),  Tracker::Panel::Clock, false);
   makeInput(this, Vec(25.42, 230.96),  Tracker::Panel::Channel2_Pass, true);
   makeInput(this, Vec(24.17, 194.01),  Tracker::Panel::Channel1_Pass, true);

   makeOutput(this, Vec(64.08, 230.96), Tracker::Panel::Channel2_Output, true);
   makeOutput(this, Vec(62.83, 194.01), Tracker::Panel::Channel1_Output, true);

   makeLED(this, Vec(54.09, 309.20), Tracker::Panel::RGB_Internal_Status);
   makeLED(this, Vec(54.09, 294.64), Tracker::Panel::RGB_Remote_Status);
   makeLED(this, Vec(54.09, 280.08), Tracker::Panel::RGB_Input_Status);

   makeOLED(this, Vec(11.25, 47.00), Tracker::Panel::Pixels_Display, 60, 120);
}

