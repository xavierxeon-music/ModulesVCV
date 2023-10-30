#ifndef ClockAndBarCounterH
#define ClockAndBarCounterH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>
#include <Music/TimeCode.h>

#include <SvinMasterClock.h>
#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class ClockAndBarCounter : public Svin::Module, public Svin::MidiInput, public Svin::MasterClock
{
public:
   struct Panel;

public:
   ClockAndBarCounter();
   ~ClockAndBarCounter();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   inline void setup();
   void connectToMidiDevice();

   void clockTick() override;
   void songPosition(const uint16_t& position) override;

private:
   // midi
   Svin::ButtonLED connectionButton;
   Counter midiTickCounter;
   bool blockAdvanceTempo;

   // manual
   Svin::Output runOutput;
   Svin::Output clockOutput;
   Svin::Output resetOutput;

   // override
   Svin::Input clockInput;
   Svin::Input resetInput;

   // display
   Svin::DisplayOLED::Controller displayController;
};

// widget

class ClockAndBarCounterWidget : public Svin::ModuleWidget
{
public:
   ClockAndBarCounterWidget(ClockAndBarCounter* module);

private:
   inline void setup();
};

#ifndef ClockAndBarCounterHPP
#include "ClockAndBarCounter.hpp"
#endif // NOT ClockAndBarCounterHPP

#endif // NOT ClockAndBarCounterH
