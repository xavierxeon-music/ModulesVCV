#ifndef TrackerWorkerHPP
#define TrackerWorkerHPP

#include "TrackerWorker.h"

#include <SvinOrigin.h>

struct TrackerWorker::Panel
{
   enum ParamId
   {
      // buttons
      Mode = 0,
      // switches
      // ledbuttons
      Loop = 1,
      // knobs
      // sliders
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      // oled
      Pixels_Display = 0,
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Upload = 0,
      Group2_Pass = 1,
      Group1_Pass = 2,
      INPUTS_LEN = 3
   };

   enum OutputId
   {
      Group2_Output = 0,
      Group1_Output = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Loop = 0,
      // sliders
      LIGHTS_LEN = 3
   };

};

void TrackerWorker::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Mode, "Mode");

   configButton(Panel::Loop, "Loop");

   configInput(Panel::Upload, "Upload");
   configInput(Panel::Group2_Pass, "Group2_Pass");
   configInput(Panel::Group1_Pass, "Group1_Pass");

   configOutput(Panel::Group2_Output, "Group2_Output");
   configOutput(Panel::Group1_Output, "Group1_Output");
}

void TrackerWorkerWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Sequencer/TrackerWorker.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(97.56, 232.00), TrackerWorker::Panel::Mode);

   makeLEDButton(this, Vec(43.21, 232.00), TrackerWorker::Panel::Loop, TrackerWorker::Panel::RGB_Loop);

   makeInput(this, Vec(95.83, 355.81),  TrackerWorker::Panel::Upload, false);
   makeInput(this, Vec(24.17, 302.21),  TrackerWorker::Panel::Group2_Pass, true);
   makeInput(this, Vec(24.17, 268.71),  TrackerWorker::Panel::Group1_Pass, true);

   makeOutput(this, Vec(95.83, 302.21), TrackerWorker::Panel::Group2_Output, true);
   makeOutput(this, Vec(95.83, 268.71), TrackerWorker::Panel::Group1_Output, true);

   makeOLED(this, Vec(9.00, 32.00), TrackerWorker::Panel::Pixels_Display, 100, 180);
}

Model* modelTrackerWorker = Svin::Origin::the()->addModule<TrackerWorker, TrackerWorkerWidget>("TrackerWorker");

#endif // NOT TrackerWorkerHPP
