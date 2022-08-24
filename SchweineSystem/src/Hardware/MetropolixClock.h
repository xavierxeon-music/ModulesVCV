#ifndef MetropolixClockH
#define MetropolixClockH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>

#include <SyModule.h>
#include <SyModuleWidget.h>

#include <SyButtonLED.h>
#include <SyOutput.h>

class MetropolixClock : public Sy::Module
{
public:
   struct Panel;

public:
   MetropolixClock();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void processMessage(const midi::Message& msg);
   void connectToMidiDevice();

private:
   // midi
   midi::InputQueue midiInput;
   Sy::ButtonLED connectionButton;
   // tempo
   Counter tickCounter;
   bool doNotAdvanceTempo;
   Tempo tempo;
   dsp::PulseGenerator clockTick;
   dsp::PulseGenerator clockReset;
};

// widget

class MetropolixClockWidget : public Sy::ModuleWidget
{
public:
   MetropolixClockWidget(MetropolixClock* module);

private:
   void setup();
};

#endif // NOT MetropolixClockH
