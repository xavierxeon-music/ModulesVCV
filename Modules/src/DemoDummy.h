#ifndef DemoDummyH
#define DemoDummyH

#include <rack.hpp>
using namespace rack;

class DemoDummy : public Module
{
public:
   struct Data;

public:
   DemoDummy();
   ~DemoDummy();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

struct DemoDummyWidget : ModuleWidget
{
   DemoDummyWidget(DemoDummy* module);
};

#endif // DemoDummyH
