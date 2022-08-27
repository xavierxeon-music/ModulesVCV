#ifndef TimeLordFlameCCH
#define TimeLordFlameCCH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SvinButtonLED.h>
#include <SvinCommon.h>
#include <SvinInput.h>
#include <SvinMidiOutput.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinSwitch.h>

class TimeLordFlameCC : public Svin::Module, private Svin::MidiOutput
{
public:
   struct Panel;

public:
   TimeLordFlameCC();

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
   Svin::Input::List inputList;
   uint8_t controllerValueStore[16];
   // half voltage
   Svin::Switch::List fullVoltSwitchList;
};

class TimeLordFlameCCWidget : public Svin::ModuleWidget
{
public:
   TimeLordFlameCCWidget(TimeLordFlameCC* module);

private:
   void setup();
};

#endif // NOT TimeLordFlameCCH
