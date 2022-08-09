#include "PictureMesh.h"
#include "PictureMeshPanel.h"

#include <SchweineSystemMaster.h>

PictureMesh::PictureMesh()
   : SchweineSystem::Module()
{
   setup();
}
void PictureMesh::process(const ProcessArgs& args)
{
}


// widget

PictureMeshWidget::PictureMeshWidget(PictureMesh* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelPictureMesh = SchweineSystem::Master::the()->addModule<PictureMesh, PictureMeshWidget>("PictureMesh");
