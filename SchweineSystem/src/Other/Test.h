#ifndef TestH
#define TestH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemMeter.h>

class Test : public Module
{
public:
   struct Panel;

public:
   Test();
   ~Test();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   Panel* panel;
   SchweineSystem::Meter::Controller meter;
};

class TestWidget : public ModuleWidget
{
public:
   TestWidget(Test* module);

private:
   SvgPanel* setup(Test* module);
};

#endif // NOT TestH
