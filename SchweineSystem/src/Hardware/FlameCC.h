#ifndef FlameCCH
#define FlameCCH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SyButtonLED.h>
#include <SyCommon.h>
#include <SyInput.h>
#include <SyMidiOutput.h>
#include <SyModule.h>
#include <SyModuleWidget.h>
#include <SySwitch.h>

class FlameCC : public Sy::Module, private Sy::MidiOutput
{
public:
   struct Panel;

public:
   FlameCC();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();
   void sendSysEx();

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   // midi
   Sy::ButtonLED connectionButton;
   Range::Mapper voltageToCcValue;
   // outputs
   Sy::Input::List inputList;
   uint8_t controllerValueStore[16];
   // half voltage
   Sy::Switch::List fullVoltSwitchList;
};

class FlameCCWidget : public Sy::ModuleWidget
{
public:
   FlameCCWidget(FlameCC* module);

private:
   void setup();
};

#endif // NOT FlameCCH
