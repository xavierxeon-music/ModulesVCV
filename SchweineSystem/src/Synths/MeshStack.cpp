#include "MeshStack.h"
#include "MeshStackPanel.h"

#include <SchweineSystemMaster.h>

MeshStack::MeshStack()
   : SchweineSystem::Module()
{
   setup();
}
void MeshStack::process(const ProcessArgs& args)
{
}


// widget

MeshStackWidget::MeshStackWidget(MeshStack* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelMeshStack = SchweineSystem::Master::the()->addModule<MeshStack, MeshStackWidget>("MeshStack");
