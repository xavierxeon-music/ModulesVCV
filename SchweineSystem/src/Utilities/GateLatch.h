#ifndef GateLatchH
#define GateLatchH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class GateLatch : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   GateLatch();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const SchweineSystem::Json::Object& rootObject) override;
   void save(SchweineSystem::Json::Object& rootObject) override;

private:
   SchweineSystem::Input::List inputList;
   SchweineSystem::Output::List outputList;
   SchweineSystem::LED::List lightList;

   dsp::BooleanTrigger triggers[8];
   dsp::PulseGenerator activity[8];
   bool latches[8];

   dsp::BooleanTrigger resetTrigger;
};

class GateLatchWidget : public SchweineSystem::ModuleWidget
{
public:
   GateLatchWidget(GateLatch* module);

private:
   void setup();
};

#endif // NOT GateLatchH
