#ifndef MidiCVH
#define MidiCVH

#include <rack.hpp>
using namespace rack;

#include <SchweineSystemExapnder.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemExpanderMessages.h>

class MidiCV : public SchweineSystem::Module, public SchweineSystem::Exapnder<SchweineSystem::BusMidi>
{
public:
   struct Panel;

public:
   MidiCV();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
};

// widget

class MidiCVWidget : public SchweineSystem::ModuleWidget
{
public:
   MidiCVWidget(MidiCV* module);

private:
   void setup();
};

#endif // NOT MidiCVH
