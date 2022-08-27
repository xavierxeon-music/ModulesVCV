#ifndef TimeLordCompanionH
#define TimeLordCompanionH

#include <rack.hpp>
using namespace rack;

#include <SvinButtonLED.h>
#include <SvinExapnder.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinSvgImage.h>
#include <SvinSwitch.h>

#include "TimeLord.h"

class TimeLordCompanion : public Svin::Module, public Svin::Exapnder<BusTimeLord>
{
public:
   struct Panel;

public:
   TimeLordCompanion();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   // steady
   Svin::Input::List steadyInputList;
   Svin::ButtonLED::List steadyButtonList;
   bool buttonSteady[8];
   // silence
   Svin::Switch::List silenceSwitches;
};

// widget

class TimeLordCompanionWidget : public Svin::ModuleWidget
{
public:
   TimeLordCompanionWidget(TimeLordCompanion* module);

private:
   void setup();
   void preDraw() override;

private:
   Svin::SvgImage* logoWidget;
};

#endif // NOT TimeLordCompanionH
