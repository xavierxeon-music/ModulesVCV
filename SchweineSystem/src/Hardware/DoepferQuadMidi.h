#ifndef DoepferQuadMidiH
#define DoepferQuadMidiH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemExapnder.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemExpanderMessages.h>

class DoepferQuadMidi : public SchweineSystem::Module, private SchweineSystem::MidiOutput, public SchweineSystem::Exapnder<SchweineSystem::BusMidi>
{
public:
   struct Panel;

public:
   DoepferQuadMidi();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();

private:
   SchweineSystem::ButtonLED connectionButton;
};

// widget

class DoepferQuadMidiWidget : public SchweineSystem::ModuleWidget
{
public:
   DoepferQuadMidiWidget(DoepferQuadMidi* module);

private:
   void setup();
};

#endif // NOT DoepferQuadMidiH
