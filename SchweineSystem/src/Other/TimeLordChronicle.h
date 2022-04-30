#ifndef TimeLordChronicleH
#define TimeLordChronicleH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>
#include <SchweineSystemLightMeter.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class TimeLordChronicle : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   TimeLordChronicle();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   SchweineSystem::Input::List inputList;
   SchweineSystem::LightMeter::Controller::List lightMeterList;
   SchweineSystem::LCDDisplay::Controller::List displayList;
   Range::Mapper voltageToValue;
};

class TimeLordChronicleWidget : public SchweineSystem::ModuleWidget
{
public:
   TimeLordChronicleWidget(TimeLordChronicle* module);

private:
   void setup();
};

#endif // NOT TimeLordChronicleH
