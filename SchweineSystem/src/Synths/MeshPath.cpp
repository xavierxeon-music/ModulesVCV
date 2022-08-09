#include "MeshPath.h"
#include "MeshPathPanel.h"

#include <SchweineSystemMaster.h>

MeshPath::MeshPath()
   : SchweineSystem::Module()
{
   setup();
}
void MeshPath::process(const ProcessArgs& args)
{
}


// widget

MeshPathWidget::MeshPathWidget(MeshPath* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelMeshPath = SchweineSystem::Master::the()->addModule<MeshPath, MeshPathWidget>("MeshPath");
