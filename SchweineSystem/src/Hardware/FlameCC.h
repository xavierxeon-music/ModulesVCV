#ifndef FlameCCH
#define FlameCCH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemCommon.h>
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

   void load(const SchweineSystem::Json::Object& rootObject) override;
   void save(SchweineSystem::Json::Object& rootObject) override;

private:
   // midi
   SchweineSystem::ButtonLED connectionButton;
   Range::Mapper voltageToCcValue;
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
