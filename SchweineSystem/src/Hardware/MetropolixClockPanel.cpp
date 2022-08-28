#include "MetropolixClockPanel.h"
#include "MetropolixClock.h"

#include <SvinMaster.h>

void MetropolixClock::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Override_Reset, "Override_Reset");
   configInput(Panel::Override_Clock, "Override_Clock");

   configOutput(Panel::Reset, "Reset");
   configOutput(Panel::Clock, "Clock");
}

void MetropolixClockWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/Hardware/MetropolixClock.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(68.53, 261.21), MetropolixClock::Panel::Connect, MetropolixClock::Panel::RGB_Connect);

   makeInput(this, Vec(24.17, 355.61), MetropolixClock::Panel::Override_Reset, false);
   makeInput(this, Vec(24.17, 306.49), MetropolixClock::Panel::Override_Clock, false);

   makeOutput(this, Vec(80.83, 355.83), MetropolixClock::Panel::Reset, false);
   makeOutput(this, Vec(80.82, 306.49), MetropolixClock::Panel::Clock, false);

   makeOLED(this, Vec(10.00, 67.98), MetropolixClock::Panel::Pixels_Display, 83, 170);
}
