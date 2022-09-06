#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SvinOrigin.h>

void MeshStack::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Two, 0.0f, 1.0f, 0.0f, "Two");
   configSwitch(Panel::One, 0.0f, 1.0f, 0.0f, "One");

   configParam(Panel::Mode, -1.f, 1.f, 0.f, "Mode");

   configInput(Panel::Pitch, "Pitch");

   configOutput(Panel::Out, "Out");
}

void MeshStackWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Synths/MeshStack.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeSlider(this, Vec(56.60, 242.35), MeshStack::Panel::Two, false);
   makeSlider(this, Vec(164.99, 193.20), MeshStack::Panel::One, true);

   makeKnob(this, Vec(143.98, 121.89), MeshStack::Panel::Mode, 3);

   makeInput(this, Vec(94.38, 290.07),  MeshStack::Panel::Pitch, false);

   makeOutput(this, Vec(94.38, 332.98), MeshStack::Panel::Out, false);
}

