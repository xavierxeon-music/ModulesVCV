#ifndef MeshStackH
#define MeshStackH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinInput.h>
#include <SvinKnob.h>
#include <SvinOutput.h>

class MeshStack : public Svin::Module
{
public:
   struct Panel;

public:
   MeshStack();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   void setup();

private:
   Svin::Knob knob;
};

// widget

class MeshStackWidget : public Svin::ModuleWidget
{
public:
   MeshStackWidget(MeshStack* module);

private:
   void setup();
};

#endif // NOT MeshStackH
