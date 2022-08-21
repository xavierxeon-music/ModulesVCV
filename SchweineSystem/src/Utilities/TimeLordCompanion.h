#ifndef TimeLordCompanionH
#define TimeLordCompanionH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemExapnder.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>
#include <SchweineSystemSwitch.h>

#include "TimeLord.h"

class TimeLordCompanion : public SchweineSystem::Module, public SchweineSystem::Exapnder<BusTimeLord>
{
public:
   struct Panel;

public:
   TimeLordCompanion();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const SchweineSystem::Json::Object& rootObject) override;
   void save(SchweineSystem::Json::Object& rootObject) override;

private:
   // steady
   SchweineSystem::Input::List steadyInputList;
   SchweineSystem::ButtonLED::List steadyButtonList;
   bool buttonSteady[8];
   // silence
   SchweineSystem::Switch::List silenceSwitches;
};

// widget

class TimeLordCompanionWidget : public SchweineSystem::ModuleWidget
{
public:
   TimeLordCompanionWidget(TimeLordCompanion* module);

private:
   void setup();
};

#endif // NOT TimeLordCompanionH
