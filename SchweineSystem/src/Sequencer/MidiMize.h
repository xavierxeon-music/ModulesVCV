#ifndef MidiMizeH
#define MidiMizeH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinInput.h>

class MidiMize : public Svin::Module
{
public:
   struct Panel;

public:
   MidiMize();

public:
   void process(const ProcessArgs& args) override;

private:
   struct State
   {
      uint8_t midiNote;
      bool gate;
      uint8_t velocity;

      State();
      State(const uint8_t midiNote, const bool gate, const uint8_t velocity);
      bool operator==(const State& other) const;
   };

private:
   inline void setup();
   Bytes noteOn(const uint8_t& channel, const uint8_t& midiNote, const uint8_t& velocity);
   Bytes noteOff(const uint8_t& channel, const uint8_t& midiNote);

private:
   Svin::Input pitchInput;
   Svin::Input gateInput;
   Svin::Input velocityInput;

   Range::Mapper velocityMapper;
   State lastState[16];
};

// widget

class MidiMizeWidget : public Svin::ModuleWidget
{
public:
   MidiMizeWidget(MidiMize* module);

private:
   inline void setup();
};

#ifndef MidiMizeHPP
#include "MidiMize.hpp"
#endif // NOT MidiMizeHPP

#endif // NOT MidiMizeH
