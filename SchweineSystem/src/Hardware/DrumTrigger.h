#ifndef DrumTriggerH
#define DrumTriggerH

#include <rack.hpp>
using namespace rack;

#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Flank.h>

#include <SvinButtonLED.h>
#include <SvinInput.h>

class DrumTrigger : public Svin::Module, public Svin::Midi::Output
{
public:
   struct Panel;

public:
   DrumTrigger();

public:
   void process(const ProcessArgs& args) override;
   void connectToMidiDevice();

private:
   inline void setup();

private:
   Svin::Input input;
   Svin::ButtonLED connectionButton;
   Flank flank[16];
};

// widget

class DrumTriggerWidget : public Svin::ModuleWidget
{
public:
   DrumTriggerWidget(DrumTrigger* module);

private:
   inline void setup();
};

#ifndef DrumTriggerHPP
#include "DrumTrigger.hpp"
#endif // NOT DrumTriggerHPP

#endif // NOT DrumTriggerH
