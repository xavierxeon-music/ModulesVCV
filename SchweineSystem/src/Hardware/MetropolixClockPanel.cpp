#include "MetropolixClock.h"
#include "MetropolixClockPanel.h"

#include <SyMaster.h>

void MetropolixClock::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configOutput(Panel::Reset, "Reset");
   configOutput(Panel::Clock, "Clock");
}

void MetropolixClockWidget::setup()
{
   std::string panelPath = asset::plugin(Sy::Master::the()->instance(), "res/Hardware/MetropolixClock.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(29.95, 340.14), MetropolixClock::Panel::Connect, MetropolixClock::Panel::RGB_Connect);

   makeOutput(this, Vec(30.01, 240.06), MetropolixClock::Panel::Reset, false);
   makeOutput(this, Vec(30.00, 190.72), MetropolixClock::Panel::Clock, false);
}

