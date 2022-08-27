#ifndef FlameCCSenderH
#define FlameCCSenderH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

class FlameCCSender : public Svin::Module
{
public:
   struct Panel;

public:
   FlameCCSender();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class FlameCCSenderWidget : public Svin::ModuleWidget
{
public:
   FlameCCSenderWidget(FlameCCSender* module);

private:
   void setup();
};

#endif // NOT FlameCCSenderH
