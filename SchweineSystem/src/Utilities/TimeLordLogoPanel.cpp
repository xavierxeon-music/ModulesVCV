#include "TimeLordLogo.h"
#include "TimeLordLogoPanel.h"

#include <SyMaster.h>

void TimeLordLogo::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

void TimeLordLogoWidget::setup()
{
   std::string panelPath = asset::plugin(Sy::Master::the()->instance(), "res/Utilities/TimeLordLogo.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);
}

