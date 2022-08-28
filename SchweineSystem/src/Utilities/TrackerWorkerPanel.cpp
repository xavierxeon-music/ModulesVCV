#include "TrackerWorkerPanel.h"
#include "TrackerWorker.h"

#include <SvinMaster.h>

void TrackerWorker::setup()
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
}

void TrackerWorkerWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/Utilities/TrackerWorker.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(46.10, 228.33), TrackerWorker::Panel::Display);
   makeButton(this, Vec(99.68, 228.33), TrackerWorker::Panel::ModeManual);

   makeInput(this, Vec(95.83, 355.81), TrackerWorker::Panel::Upload, false);
   makeInput(this, Vec(56.92, 355.83), TrackerWorker::Panel::Reset, false);
   makeInput(this, Vec(24.17, 355.83), TrackerWorker::Panel::Clock, false);
   makeInput(this, Vec(24.17, 300.21), TrackerWorker::Panel::Group2_Pass, true);
   makeInput(this, Vec(24.17, 266.71), TrackerWorker::Panel::Group1_Pass, true);

   makeOutput(this, Vec(95.83, 300.21), TrackerWorker::Panel::Group2_Output, true);
   makeOutput(this, Vec(95.83, 266.71), TrackerWorker::Panel::Group1_Output, true);

   makeOLED(this, Vec(9.00, 34.00), TrackerWorker::Panel::Pixels_Display, 100, 180);
}
