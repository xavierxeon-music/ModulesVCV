#ifndef PamelasClockH
#define PamelasClockH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class PamelasClock : public SchweineSystem::Module
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
   SchweineSystem::ButtonLED connectionButton;
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

class PamelasClockWidget : public SchweineSystem::ModuleWidget
{
public:
   PamelasClockWidget(PamelasClock* module);

private:
   void setup();
};

#endif // NOT PamelasClockH
