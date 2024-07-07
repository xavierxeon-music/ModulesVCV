#ifndef ClockAndBarCounterH
#define ClockAndBarCounterH

#include <rack.hpp>
using namespace rack;

#include <ableton/Link.hpp>

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

class ClockAndBarCounter : public Svin::Module, public Svin::MasterClock
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

   void emulateMidiTick(); // MIDI

private:
   ableton::Link link;

   // midi
   Counter midiTickCounter;
   Counter ppq24Counter;
   bool blockAdvanceTempo;
   bool lastRunning;

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
