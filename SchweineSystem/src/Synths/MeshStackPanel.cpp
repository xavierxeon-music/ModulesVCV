#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SchweineSystemMaster.h>

void MeshStack::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Knob_Mode, 0.f, 3.f, 0.f, "", {"Unmuted", "Muted", "Soloed", "Soloed"});

   configInput(Panel::Pitch, "Pitch");

   configOutput(Panel::Out, "Out");
}

void MeshStackWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "/Users/waspe/GitHub/MusicProjects/ModulesVCV/SchweineSystem/res/Synths/MeshStack.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeKnob(this, Vec(143.98, 121.89), MeshStack::Panel::Knob_Mode, 1);

   makeInput(this, Vec(55.54, 285.15),  MeshStack::Panel::Pitch);

   makeOutput(this, Vec(55.54, 328.06), MeshStack::Panel::Out);
}

