#ifndef TestH
#define TestH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class Test : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   Test();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

class TestWidget : public SchweineSystem::ModuleWidget
{
public:
   TestWidget(Test* module);

private:
   void setup();
};

#endif // NOT TestH
