#ifndef TimeLordServerH
#define TimeLordServerH

#include <rack.hpp>
using namespace rack;

#include <rtmidi/RtMidi.h>

#include <Blocks/PolyRamp.h>
#include <Music/Tempo.h>
#include <Tools/Range.h>

#include "SchweineSystemCommon.h"
#include "SchweineSystemLightMeter.h"
#include <SchweineSystemLight.h>

class TimeLordServer : public Module
{
public:
   struct Panel;

public:
   TimeLordServer();
   ~TimeLordServer();

public:
   void process(const ProcessArgs& args) override;

private:
   using Bytes = std::vector<uint8_t>;

   enum class LoadState
   {
      Ready,
      Receive,
      Apply
   };

private:
   void setup();
   void dataFromInput(const Bytes& message);
   static void midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData);
   static void midiError(RtMidiError::Type type, const std::string& errorText, void* userData);

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   RtMidiIn midiInput;
   static const std::string keys;
   PolyRamp ramps[16];
   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;
   Range::Mapper cvMapper;
   SchweineSystem::LightMeter::List lightMeterList;
   SchweineSystem::Output::List outputList;
   SchweineSystem::Light::List loadLightList;
   LoadState loadState;
};

class TimeLordServerWidget : public ModuleWidget
{
public:
   TimeLordServerWidget(TimeLordServer* module);

private:
   SvgPanel* setup(TimeLordServer* module);
};

#endif // NOT TimeLordServerH
