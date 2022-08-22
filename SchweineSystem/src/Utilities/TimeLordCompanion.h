#ifndef TimeLordCompanionH
#define TimeLordCompanionH

#include <rack.hpp>
using namespace rack;

#include <SyButtonLED.h>
#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>
#include <SySvgImage.h>
#include <SySwitch.h>

#include "TimeLord.h"

class TimeLordCompanion : public Sy::Module, public Sy::Exapnder<BusTimeLord>
{
public:
   struct Panel;

public:
   TimeLordCompanion();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   // steady
   Sy::Input::List steadyInputList;
   Sy::ButtonLED::List steadyButtonList;
   bool buttonSteady[8];
   // silence
   Sy::Switch::List silenceSwitches;
};

// widget

class TimeLordCompanionWidget : public Sy::ModuleWidget
{
public:
   TimeLordCompanionWidget(TimeLordCompanion* module);

private:
   void setup();
};

#endif // NOT TimeLordCompanionH
