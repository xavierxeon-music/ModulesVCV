#ifndef MeshStackH
#define MeshStackH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class MeshStack : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   MeshStack();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class MeshStackWidget : public SchweineSystem::ModuleWidget
{
public:
   MeshStackWidget(MeshStack* module);

private:
   void setup();
};

#endif // NOT MeshStackH
