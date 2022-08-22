#ifndef GateLatchH
#define GateLatchH

#include <rack.hpp>
using namespace rack;

#include <SyCommon.h>
#include <SyLED.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

class GateLatch : public Sy::Module
{
public:
   struct Panel;

public:
   GateLatch();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   Sy::Input::List inputList;
   Sy::Output::List outputList;
   Sy::LED::List lightList;

   dsp::BooleanTrigger triggers[8];
   dsp::PulseGenerator activity[8];
   bool latches[8];

   dsp::BooleanTrigger resetTrigger;
};

class GateLatchWidget : public Sy::ModuleWidget
{
public:
   GateLatchWidget(GateLatch* module);

private:
   void setup();
};

#endif // NOT GateLatchH
