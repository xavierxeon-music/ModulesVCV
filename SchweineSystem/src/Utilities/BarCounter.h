#ifndef BarCounterH
#define BarCounterH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>
#include <Music/TimeCode.h>
#include <Tools/Counter.h>

#include <SyDisplayOLED.h>
#include <SyInput.h>
#include <SyModule.h>
#include <SyModuleWidget.h>
#include <SyOutput.h>

class BarCounter : public Sy::Module
{
public:
   struct Panel;

public:
   BarCounter();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   void setup();

private:
   // tempo
   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;
   // time
   TimeCode::Duration duration;
   Sy::DisplayOLED::Controller displayController;
};

// widget

class BarCounterWidget : public Sy::ModuleWidget
{
public:
   BarCounterWidget(BarCounter* module);

private:
   void setup();
};

#endif // NOT BarCounterH
