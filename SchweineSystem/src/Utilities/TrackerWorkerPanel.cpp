#include "TrackerWorker.h"
#include "TrackerWorkerPanel.h"

#include <SvinMaster.h>

void TrackerWorker::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Mode, "Mode");

   configButton(Panel::Loop, "Loop");

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

   makeButton(this, Vec(97.56, 232.00), TrackerWorker::Panel::Mode);

   makeLEDButton(this, Vec(43.21, 232.00), TrackerWorker::Panel::Loop, TrackerWorker::Panel::RGB_Loop);

   makeInput(this, Vec(95.83, 355.81),  TrackerWorker::Panel::Upload, false);
   makeInput(this, Vec(56.92, 355.83),  TrackerWorker::Panel::Reset, false);
   makeInput(this, Vec(24.17, 355.83),  TrackerWorker::Panel::Clock, false);
   makeInput(this, Vec(24.17, 302.21),  TrackerWorker::Panel::Group2_Pass, true);
   makeInput(this, Vec(24.17, 268.71),  TrackerWorker::Panel::Group1_Pass, true);

   makeOutput(this, Vec(95.83, 302.21), TrackerWorker::Panel::Group2_Output, true);
   makeOutput(this, Vec(95.83, 268.71), TrackerWorker::Panel::Group1_Output, true);

   makeOLED(this, Vec(9.00, 32.00), TrackerWorker::Panel::Pixels_Display, 100, 180);
}

