#include "BarCounter.h"
#include "BarCounterPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void BarCounter::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Clock, "Clock");

   configText(Panel::Text_Tempo, "Tempo");

   configPixels(Panel::Pixels_Display, 64, 128, "Display");
}

void BarCounterWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/BarCounter.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(45.00, 345.45),  BarCounter::Panel::Reset);
   makeInput(this, Vec(45.00, 296.32),  BarCounter::Panel::Clock);

   makeLCD(this, Vec(17.11, 199.37), 3, BarCounter::Panel::Text_Tempo, BarCounter::Panel::RGB_Tempo);

   makeOLED(this, Vec(12.00, 50.24), BarCounter::Panel::Pixels_Display, 64, 128);
}

