#include "MetropolixClock.h"
#include "MetropolixClockPanel.h"

#include <SvinOrigin.h>

void MetropolixClock::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Override_Reset, "Override_Reset");
   configInput(Panel::Override_Clock, "Override_Clock");

   configOutput(Panel::Reset, "Reset");
}

void MetropolixClockWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Hardware/MetropolixClock.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(76.53, 261.21), MetropolixClock::Panel::Connect, MetropolixClock::Panel::RGB_Connect);

   makeInput(this, Vec(80.83, 308.08),  MetropolixClock::Panel::Override_Reset, false);
   makeInput(this, Vec(41.08, 308.57),  MetropolixClock::Panel::Override_Clock, false);

   makeOutput(this, Vec(80.83, 355.83), MetropolixClock::Panel::Reset, false);

   makeOLED(this, Vec(10.00, 61.98), MetropolixClock::Panel::Pixels_Display, 83, 170);
}

