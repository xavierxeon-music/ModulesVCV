#include "MeshPath.h"
#include "MeshPathPanel.h"

#include <SchweineSystemMaster.h>

void MeshPath::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

void MeshPathWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "/Users/waspe/GitHub/MusicProjects/ModulesVCV/SchweineSystem/res/Synths/MeshPath.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);
}

