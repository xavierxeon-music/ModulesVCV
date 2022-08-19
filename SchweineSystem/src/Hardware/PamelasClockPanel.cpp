#include "PamelasClock.h"
#include "PamelasClockPanel.h"

#include <SchweineSystemMaster.h>

void PamelasClock::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configOutput(Panel::Reset, "Reset");
   configOutput(Panel::Clock, "Clock");
}

void PamelasClockWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Hardware/PamelasClock.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(29.95, 340.14), PamelasClock::Panel::Connect, PamelasClock::Panel::RGB_Connect);

   makeOutput(this, Vec(30.01, 240.06), PamelasClock::Panel::Reset);
   makeOutput(this, Vec(30.00, 190.72), PamelasClock::Panel::Clock);
}

