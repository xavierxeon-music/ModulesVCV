#include "BarCounter.h"
#include "BarCounterPanel.h"

#include <SyMaster.h>

void BarCounter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");

   configPixels(Panel::Pixels_Display, 83, 170, "Display");
}

void BarCounterWidget::setup()
{
   std::string panelPath = asset::plugin(Sy::Master::the()->instance(), "res/Utilities/BarCounter.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(52.50, 344.93),  BarCounter::Panel::Reset, false);
   makeInput(this, Vec(52.50, 295.80),  BarCounter::Panel::Clock, false);

   makeOLED(this, Vec(10.00, 63.98), BarCounter::Panel::Pixels_Display, 83, 170);
}

