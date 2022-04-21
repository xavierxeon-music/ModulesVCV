#include "ClockTool.h"
#include "ClockToolPanel.h"

#include "SchweineSystemMaster.h"

void ClockTool::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

SvgPanel* ClockToolWidget::setup(ClockTool* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/ClockTool.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   return mainPanel;
}

