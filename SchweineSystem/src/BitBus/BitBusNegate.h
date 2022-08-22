#ifndef BitBusNegateH
#define BitBusNegateH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

#include <SyCommon.h>
#include <SyLED.h>

class BitBusNegate : public Sy::Module, public Sy::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusNegate();
   ~BitBusNegate();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   Sy::LED::List lightList;
   Sy::Param::List paramList;
   Sy::Input::List gateList;
   dsp::BooleanTrigger gateTrigger[8];
   bool gates[8];

   Sy::LED busInIndicator;
   Sy::LED busOutIndicator;
};

// widget

class BitBusNegateWidget : public Sy::ModuleWidget
{
public:
   BitBusNegateWidget(BitBusNegate* module);

private:
   void setup();
};

#endif // NOT BitBusNegateH
