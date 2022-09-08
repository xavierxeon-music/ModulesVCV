#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SvinOrigin.h>

void MeshStack::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Blue, 0.0f, 1.0f, 0.0f, "Blue");
   configSwitch(Panel::Green, 0.0f, 1.0f, 0.0f, "Green");
   configSwitch(Panel::Red, 0.0f, 1.0f, 0.0f, "Red");

   configParam(Panel::Mode, -1.f, 1.f, 0.f, "Mode");

   configInput(Panel::Pitch, "Pitch");

   configOutput(Panel::Out, "Out");
}

void MeshStackWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Synths/MeshStack.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeSlider(this, Vec(83.74, 147.50), MeshStack::Panel::Blue, MeshStack::Panel::RGB_Blue);
   makeSlider(this, Vec(68.50, 147.50), MeshStack::Panel::Green, MeshStack::Panel::RGB_Green);
   makeSlider(this, Vec(53.26, 147.50), MeshStack::Panel::Red, MeshStack::Panel::RGB_Red);

   makeKnob(this, Vec(216.14, 319.36), MeshStack::Panel::Mode, 3);

   makeInput(this, Vec(94.38, 290.07),  MeshStack::Panel::Pitch, false);

   makeOutput(this, Vec(94.38, 332.98), MeshStack::Panel::Out, false);

   makeLED(this, Vec(105.25, 147.50), MeshStack::Panel::RGB_Color);
}

