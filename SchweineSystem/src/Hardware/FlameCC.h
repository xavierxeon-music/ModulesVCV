#ifndef FlameCCH
#define FlameCCH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>
#include <SchweineSystemSwitch.h>

class FlameCC : public SchweineSystem::Module, private SchweineSystem::MidiOutput
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

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   // midi
   dsp::BooleanTrigger connectTrigger;
   Range::Mapper voltageToCcValue;
   SchweineSystem::LED connectionLight;
   // outputs
   SchweineSystem::Input::List inputList;
   uint8_t controllerValueStore[16];
   // half voltage
   SchweineSystem::Switch::List fullVoltSwitchList;
};

class FlameCCWidget : public SchweineSystem::ModuleWidget
{
public:
   FlameCCWidget(FlameCC* module);

private:
   void setup();
};

#endif // NOT FlameCCH
