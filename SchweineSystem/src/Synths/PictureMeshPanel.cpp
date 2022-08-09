#include "PictureMesh.h"
#include "PictureMeshPanel.h"

#include <SchweineSystemMaster.h>

void PictureMesh::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);
}

void PictureMeshWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "/Users/waspe/GitHub/MusicProjects/ModulesVCV/SchweineSystem/res/Synths/PictureMesh.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);
}

