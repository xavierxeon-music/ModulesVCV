#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SchweineSystemMaster.h>

void MeshStack::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Pitch, "Pitch");

   configOutput(Panel::Out, "Out");
}

void MeshStackWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "/Users/waspe/GitHub/MusicProjects/ModulesVCV/SchweineSystem/res/Synths/MeshStack.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(55.54, 266.05),  MeshStack::Panel::Pitch);

   makeOutput(this, Vec(125.26, 327.29), MeshStack::Panel::Out);
}

