#ifndef MidiCVH
#define MidiCVH

#include <rack.hpp>
using namespace rack;

#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

#include "MidiReplay.h"

class MidiCV : public Sy::Module, public Sy::Exapnder<BusMidi>
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

class MidiCVWidget : public Sy::ModuleWidget
{
public:
   MidiCVWidget(MidiCV* module);

private:
   void setup();
};

#endif // NOT MidiCVH
