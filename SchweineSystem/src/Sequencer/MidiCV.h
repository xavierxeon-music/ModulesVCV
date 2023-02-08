#ifndef MidiCVH
#define MidiCVH

#include <rack.hpp>
using namespace rack;

#include <Midi/MidiParser.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinOutput.h>

class MidiCV : public Svin::Module, public Midi::Parser
{
public:
   struct Panel;

public:
   MidiCV();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
   inline void noteOn(const Midi::Channel& channel, const uint8_t& midiNote, const Midi::Velocity& velocity) override;
   inline void noteOff(const Midi::Channel& channel, const uint8_t& midiNote) override;
   inline void resetBuffer();

private:
   Svin::Output pitchOutput;
   Svin::Output gateOutput;
   Svin::Output velocityOutput;

   float pitchBuffer[16];
   bool gateBuffer[16];
   float velocityBuffer[16];
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
