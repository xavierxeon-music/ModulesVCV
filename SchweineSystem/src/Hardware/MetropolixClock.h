#ifndef MetropolixClockH
#define MetropolixClockH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>
#include <Music/TimeCode.h>

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class MetropolixClock : public Svin::Module, public Svin::MasterClock
{
public:
   struct Panel;

public:
   MetropolixClock();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   void setup();
   void connectToMidiDevice();

private:
   // midi
   midi::InputQueue midiInput;
   Svin::ButtonLED connectionButton;
   Counter midiTickCounter;

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
   void setup();
};

#endif // NOT MetropolixClockH
