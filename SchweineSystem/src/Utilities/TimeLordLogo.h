#ifndef TimeLordLogoH
#define TimeLordLogoH

#include <rack.hpp>
using namespace rack;

#include <SyModule.h>
#include <SyModuleWidget.h>

class TimeLordLogo : public Sy::Module
{
public:
   struct Panel;

public:
   TimeLordLogo();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class TimeLordLogoWidget : public Sy::ModuleWidget
{
public:
   TimeLordLogoWidget(TimeLordLogo* module);

private:
   void setup();
};

#endif // NOT TimeLordLogoH
