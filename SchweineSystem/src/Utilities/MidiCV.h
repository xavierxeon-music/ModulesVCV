#ifndef MidiCVH
#define MidiCVH

#include <rack.hpp>
using namespace rack;

#include "MidiReplay.h"
#include <SvinExapnder.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinOutput.h>

class MidiCV : public Svin::Module, public Svin::Exapnder<BusMidi>
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

class MidiCVWidget : public Svin::ModuleWidget
{
public:
   MidiCVWidget(MidiCV* module);

private:
   void setup();
};

#endif // NOT MidiCVH
