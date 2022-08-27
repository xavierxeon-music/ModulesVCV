#ifndef TrackerH
#define TrackerH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

class Tracker : public Svin::Module
{
public:
   struct Panel;

public:
   Tracker();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class TrackerWidget : public Svin::ModuleWidget
{
public:
   TrackerWidget(Tracker* module);

private:
   void setup();
};

#endif // NOT TrackerH
