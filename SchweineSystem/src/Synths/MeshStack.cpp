#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SvinOrigin.h>

MeshStack::MeshStack()
   : Svin::Module()
   , knob(this, Panel::Knob_Mode)
{
   setup();

   knob.setRange(0, 10);
   knob.enableSteps(true, 0.5);
}

void MeshStack::process(const ProcessArgs& args)
{
   knob.setValue(5);
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
