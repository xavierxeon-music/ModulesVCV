#ifndef MidiMizeH
#define MidiMizeH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinKnob.h>

class MidiMize : public Svin::Module
{
public:
   struct Panel;

public:
   MidiMize();

public:
   void process(const ProcessArgs& args) override;

private:
   struct DrumState
   {
      bool active = false;
      dsp::PulseGenerator pulse;

      bool operator!=(const DrumState& other) const;
   };

private:
   inline void setup();
   void updateDisplays() override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::Knob::List selectKnobList;
   Svin::DisplayLCD::Controller::List channelDisplayList;
   Svin::Input::List pitchInputList;
   Svin::Input::List gateInputList;
   Svin::Input::List velocityInputList;

   Range::Mapper velocityMapper;

   Svin::Input::List drumTriggerList;
   DrumState drumState[8];
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
