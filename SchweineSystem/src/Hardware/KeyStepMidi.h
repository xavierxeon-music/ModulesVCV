#ifndef KeyStepMidiH
#define KeyStepMidiH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemExapnder.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemExpanderMessages.h>

class KeyStepMidi : public SchweineSystem::Module, private SchweineSystem::MidiOutput, public SchweineSystem::Exapnder<SchweineSystem::BusMidi>
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
