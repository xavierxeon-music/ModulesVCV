#ifndef FlameCCH
#define FlameCCH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLight.h>

class FlameCC : public Module
{
public:
   struct Panel;

public:
   FlameCC();
   ~FlameCC();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();

private:
   // midi
   midi::Output midiOutput;
   dsp::BooleanTrigger connectTrigger;
   Range::Mapper voltageToCcValue;
   SchweineSystem::Light connectionLight;
   // outputs
   SchweineSystem::Input::List inputList;
};

class FlameCCWidget : public ModuleWidget
{
public:
   FlameCCWidget(FlameCC* module);

private:
   SvgPanel* setup(FlameCC* module);
};

#endif // NOT FlameCCH
