#ifndef MidiCVH
#define MidiCVH

#include <rack.hpp>
using namespace rack;

#include "MidiReplay.h"
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinOutput.h>

class MidiCV : public Svin::Module
{
public:
   struct Panel;

public:
   MidiCV();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

private:
   Svin::Output pitchOutput;
   Svin::Output gateOutput;
   Svin::Output velocityOutput;
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
