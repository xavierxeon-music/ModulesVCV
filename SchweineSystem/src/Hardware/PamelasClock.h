#ifndef PamelasClockH
#define PamelasClockH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>

#include <SyButtonLED.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

class PamelasClock : public Sy::Module
{
public:
   struct Panel;

public:
   PamelasClock();

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
   dsp::BooleanTrigger tickTrigger;
   dsp::PulseGenerator clockReset;
   dsp::BooleanTrigger resetTrigger;
};

// widget

class PamelasClockWidget : public Sy::ModuleWidget
{
public:
   PamelasClockWidget(PamelasClock* module);

private:
   void setup();
};

#endif // NOT PamelasClockH
