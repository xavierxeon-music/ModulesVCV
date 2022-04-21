#ifndef ClockToolH
#define ClockToolH

#include <rack.hpp>
using namespace rack;

class ClockTool : public Module
{
public:
   struct Panel;

public:
   ClockTool();
   ~ClockTool();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

class ClockToolWidget : public ModuleWidget
{
public:
   ClockToolWidget(ClockTool* module);

private:
   SvgPanel* setup(ClockTool* module);
};

#endif // NOT ClockToolH
