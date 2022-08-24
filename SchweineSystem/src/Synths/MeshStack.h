#ifndef MeshStackH
#define MeshStackH

#include <rack.hpp>
using namespace rack;

#include <SyInput.h>
#include <SyModule.h>
#include <SyModuleWidget.h>
#include <SyOutput.h>

class MeshStack : public Sy::Module
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

class MeshStackWidget : public Sy::ModuleWidget
{
public:
   MeshStackWidget(MeshStack* module);

private:
   void setup();
};

#endif // NOT MeshStackH
