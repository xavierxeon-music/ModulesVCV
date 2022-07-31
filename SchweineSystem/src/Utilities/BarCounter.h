#ifndef BarCounterH
#define BarCounterH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>
#include <Music/TimeCode.h>
#include <Tools/Counter.h>

#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class BarCounter : public SchweineSystem::Module
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
   SchweineSystem::DisplayOLED::Controller displayController;
};

// widget

class BarCounterWidget : public SchweineSystem::ModuleWidget
{
public:
   BarCounterWidget(BarCounter* module);

private:
   void setup();
};

#endif // NOT BarCounterH
