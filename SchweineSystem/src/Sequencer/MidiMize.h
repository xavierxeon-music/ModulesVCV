#ifndef MidiMizeH
#define MidiMizeH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

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
   inline void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::Knob::List selectKnobList;
   Svin::DisplayLCD::Controller::List channelDisplayList;
   Svin::Input::List pitchInputList;
   Svin::Input::List gateInputList;
   Svin::Input::List velocityInputList;
   bool gateActive[4];

   Svin::Input::List drumTriggerList;
   bool triggerActive[8];
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
