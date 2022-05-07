#ifndef EqualizerH
#define EqualizerH

#include <rack.hpp>
using namespace rack;

#include <Effect/StateVariableFilter.h>

#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class Equalizer : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   Equalizer();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void onSampleRateChange(const SampleRateChangeEvent& e) override;

private:
   StateVariableFilter filter;
   bool asNote;
   dsp::BooleanTrigger quantiseTrigger;
   SchweineSystem::LED quantiseLight;
   SchweineSystem::DisplayLCD::Controller frequencyDisplay;
};

class EqualizerWidget : public SchweineSystem::ModuleWidget
{
public:
   EqualizerWidget(Equalizer* module);

private:
   void setup();
};

#endif // NOT EqualizerH
