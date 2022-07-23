#ifndef SelectH
#define SelectH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class Select : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   Select();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup() override;
};

class SelectWidget : public SchweineSystem::ModuleWidget
{
public:
   SelectWidget(Select* module);

private:
   void setup();
};

#endif // NOT SelectH
