#ifndef BitBusNegateH
#define BitBusNegateH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SchweineSystemExapnder.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

class BitBusNegate : public SchweineSystem::Module, public SchweineSystem::Exapnder<BitBusMessage>
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

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   SchweineSystem::LED::List lightList;
   SchweineSystem::Param::List paramList;
   SchweineSystem::Input::List gateList;
   dsp::BooleanTrigger gateTrigger[8];
   bool gates[8];

   SchweineSystem::LED busInIndicator;
   SchweineSystem::LED busOutIndicator;
};

// widget

class BitBusNegateWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusNegateWidget(BitBusNegate* module);

private:
   void setup();
};

#endif // NOT BitBusNegateH
