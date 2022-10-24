#ifndef MetropolixClockH
#define MetropolixClockH

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

class MetropolixClock : public Svin::Module, public Svin::Midi::Input, public Svin::MasterClock
{
public:
   struct Panel;

public:
   MetropolixClock();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   inline void setup();
   void connectToMidiDevice();

   void midiClockTick() override;
   void songPosition(const uint16_t position) override;

private:
   // midi
   Svin::ButtonLED connectionButton;
   Counter midiTickCounter;
   bool blockAdvanceTempo;

   // manual
   Svin::Output resetOutput;

   // override
   Svin::Input clockInput;
   Svin::Input resetInput;

   // display
   Svin::DisplayOLED::Controller displayController;
};

// widget

class MetropolixClockWidget : public Svin::ModuleWidget
{
public:
   MetropolixClockWidget(MetropolixClock* module);

private:
   inline void setup();
};

#ifndef MetropolixClockHPP
#include "MetropolixClock.hpp"
#endif // NOT MetropolixClockHPP

#endif // NOT MetropolixClockH
