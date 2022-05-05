#ifndef KeyStepH
#define KeyStepH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>
#include <SchweineSystemLight.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class KeyStep : public SchweineSystem::Module, private SchweineSystem::MidiOutput
{
public:
   struct Panel;

public:
   KeyStep();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();
   void sendProgramChange(uint8_t channel);
   void updateDisplay(uint8_t channel);

private:
   // midi
   dsp::BooleanTrigger connectTrigger;
   SchweineSystem::Light connectionLight;
   // patterns
   SchweineSystem::Input::List inputList;
   uint8_t patterns[4];
   Range::Mapper inputMapper;
   // manual pattern
   SchweineSystem::LCDDisplay::Controller::List displayList;
   SchweineSystem::Param::List downButtonList;
   SchweineSystem::Param::List upButtonList;
   dsp::BooleanTrigger downTriggers[4];
   dsp::BooleanTrigger upTriggers[4];
};

class KeyStepWidget : public SchweineSystem::ModuleWidget
{
public:
   KeyStepWidget(KeyStep* module);

private:
   void setup();
};

#endif // NOT KeyStepH
