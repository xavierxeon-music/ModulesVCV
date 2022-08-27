#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SvinMaster.h>

MeshStack::MeshStack()
   : Svin::Module()
{
   setup();
}
void MeshStack::process(const ProcessArgs& args)
{
}

// widget

MeshStackWidget::MeshStackWidget(MeshStack* module)
   : Svin::ModuleWidget(module)
{
   setup();
}

Model* modelMeshStack = Svin::Master::the()->addModule<MeshStack, MeshStackWidget>("MeshStack");
