#ifndef PictureMeshH
#define PictureMeshH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class PictureMesh : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   PictureMesh();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class PictureMeshWidget : public SchweineSystem::ModuleWidget
{
public:
   PictureMeshWidget(PictureMesh* module);

private:
   void setup();
};

#endif // NOT PictureMeshH
