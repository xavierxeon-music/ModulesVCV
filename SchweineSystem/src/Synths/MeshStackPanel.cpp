#include "MeshStackPanel.h"
#include "MeshStack.h"

#include <SvinMaster.h>

void MeshStack::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configParam(Panel::Knob_Mode, -1.f, 1.f, 0.f, "");

   configInput(Panel::Pitch, "Pitch");

   configOutput(Panel::Out, "Out");
}

void MeshStackWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/Synths/MeshStack.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeKnob(this, Vec(143.98, 121.89), MeshStack::Panel::Knob_Mode, 1);

   makeInput(this, Vec(55.54, 285.15), MeshStack::Panel::Pitch);

   makeOutput(this, Vec(55.54, 328.06), MeshStack::Panel::Out);
}
