#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SvinOrigin.h>

MeshStack::MeshStack()
   : Svin::Module()
   , knob(this, Panel::Mode)
   , slider(this, Panel::Two, Panel::RGB_Two)
{
   setup();

   knob.setRange(0, 10);
   knob.enableSteps(true, 0.5);

   slider.setRange(0, 10);
   slider.enableSteps(true, 0.5);
}

void MeshStack::process(const ProcessArgs& args)
{
   const float precentage = slider.getValue() / 10.0;
   const uint8_t red = static_cast<uint8_t>(255 * precentage);
   slider.setColor(Svin::Color{red, 0, 0});
}

void MeshStack::updateDisplays()
{
}

// widget

MeshStackWidget::MeshStackWidget(MeshStack* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelMeshStack = Svin::Origin::the()->addModule<MeshStack, MeshStackWidget>("MeshStack");
