#ifndef MeshPathH
#define MeshPathH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class MeshPath : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   MeshPath();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class MeshPathWidget : public SchweineSystem::ModuleWidget
{
public:
   MeshPathWidget(MeshPath* module);

private:
   void setup();
};

#endif // NOT MeshPathH
