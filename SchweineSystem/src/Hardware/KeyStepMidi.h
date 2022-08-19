#ifndef KeyStepMidiH
#define KeyStepMidiH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include "MidiBusModule.h"

class KeyStepMidi : public SchweineSystem::Module, public MidiBusModule
{
public:
   struct Panel;

public:
   KeyStepMidi();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();

private:
   SchweineSystem::ButtonLED connectionButton;
};

// widget

class KeyStepMidiWidget : public SchweineSystem::ModuleWidget
{
public:
   KeyStepMidiWidget(KeyStepMidi* module);

private:
   void setup();
};

#endif // NOT KeyStepMidiH
