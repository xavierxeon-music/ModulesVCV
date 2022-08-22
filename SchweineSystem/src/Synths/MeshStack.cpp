#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SyMaster.h>

MeshStack::MeshStack()
   : Sy::Module()
{
   setup();
}
void MeshStack::process(const ProcessArgs& args)
{
}


// widget

MeshStackWidget::MeshStackWidget(MeshStack* module)
: Sy::ModuleWidget(module)
{
   setup();
}

Model* modelMeshStack = Sy::Master::the()->addModule<MeshStack, MeshStackWidget>("MeshStack");
