#ifndef BitBusNegateH
#define BitBusNegateH


#include "BitBusCommon.h"
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

class BitBusNegate : public SchweineSystem::Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusNegate();
   ~BitBusNegate();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup() override;

   void onAdd(const AddEvent& e) override;
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   SchweineSystem::LED::List lightList;
   SchweineSystem::Param::List paramList;
   SchweineSystem::Input::List gateList;
   dsp::BooleanTrigger gateTrigger[8];
   bool gates[8];
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
