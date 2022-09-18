#ifndef GateLatchH
#define GateLatchH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinCommon.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinOutput.h>

class GateLatch : public Svin::Module
{
public:
   struct Panel;

public:
   GateLatch();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::Input::List inputList;
   Svin::Output::List outputList;
   Svin::LED::List lightList;

   dsp::BooleanTrigger triggers[8];
   dsp::PulseGenerator activity[8];
   bool latches[8];

   dsp::BooleanTrigger resetTrigger;
};

class GateLatchWidget : public Svin::ModuleWidget
{
public:
   GateLatchWidget(GateLatch* module);

private:
   inline void setup();
};

#ifndef GateLatchHPP
#include "GateLatch.hpp"
#endif // NOT GateLatchHPP

#endif // NOT GateLatchH
