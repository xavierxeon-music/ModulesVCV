#ifndef BitBusNegateH
#define BitBusNegateH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyButtonLED.h>
#include <SyCommon.h>
#include <SyExapnder.h>
#include <SyInput.h>
#include <SyLED.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

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
   Sy::ButtonLED::List latchList;
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
