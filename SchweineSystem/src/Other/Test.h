#ifndef TestH
#define TestH

#include <rack.hpp>
using namespace rack;

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
};

class TestWidget : public ModuleWidget
{
public:
   TestWidget(Test* module);

private:
   SvgPanel* setup(Test* module);
};

#endif // NOT TestH
