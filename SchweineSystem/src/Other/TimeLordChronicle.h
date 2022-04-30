#ifndef TimeLordChronicleH
#define TimeLordChronicleH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class TimeLordChronicle : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   TimeLordChronicle();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

class TimeLordChronicleWidget : public SchweineSystem::ModuleWidget
{
public:
   TimeLordChronicleWidget(TimeLordChronicle* module);

private:
   void setup();
};

#endif // NOT TimeLordChronicleH
