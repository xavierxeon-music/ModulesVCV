#ifndef EqualizerH
#define EqualizerH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemLCDDisplay.h>
#include <SchweineSystemLight.h>
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

private:
   bool asNote;
   dsp::BooleanTrigger quantiseTrigger;
   SchweineSystem::Light quantiseLight;
   SchweineSystem::LCDDisplay::Controller frequencyDisplay;
};

class EqualizerWidget : public SchweineSystem::ModuleWidget
{
public:
   EqualizerWidget(Equalizer* module);

private:
   void setup();
};

#endif // NOT EqualizerH
