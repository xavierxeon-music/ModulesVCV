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
   inline void setup();
};

// widget

class MidiCVWidget : public Svin::ModuleWidget
{
public:
   MidiCVWidget(MidiCV* module);

private:
   inline void setup();
};

#ifndef MidiCVHPP
#include "MidiCV.hpp"
#endif // NOT MidiCVHPP

#endif // NOT MidiCVH
