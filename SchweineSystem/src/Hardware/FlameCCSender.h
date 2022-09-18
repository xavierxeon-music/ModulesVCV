#ifndef FlameCCSenderH
#define FlameCCSenderH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinInput.h>
#include <SvinSwitch.h>

class FlameCCSender : public Svin::Module, private Svin::Midi::Output
{
public:
   struct Panel;

public:
   FlameCCSender();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
   void connectToMidiDevice();
   void sendSysEx();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   // midi
   Svin::ButtonLED connectionButton;
   Range::Mapper voltageToCcValue;
   // outputs
   Svin::Input input;
   uint8_t valueStore[16];
   // half voltage
   Svin::Switch fullVoltSwitch;
};

// widget

class FlameCCSenderWidget : public Svin::ModuleWidget
{
public:
   FlameCCSenderWidget(FlameCCSender* module);

private:
   inline void setup();
};

#ifndef FlameCCSenderHPP
#include "FlameCCSender.hpp"
#endif // NOT FlameCCSenderHPP

#endif // NOT FlameCCSenderH
