#ifndef FlameCCSenderH
#define FlameCCSenderH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SvinMidiOutput.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinInput.h>
#include <SvinSwitch.h>

class FlameCCSender : public Svin::Module, private Svin::MidiOutput
{
public:
   struct Panel;

public:
   FlameCCSender();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
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
   void setup();
};

#endif // NOT FlameCCSenderH
