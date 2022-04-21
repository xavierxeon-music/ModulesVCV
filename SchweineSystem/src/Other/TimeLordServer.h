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
#include <SchweineSystemLCDDisplay.h>
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

   enum DisplayMode
   {
      Division,
      StageCount,
      StageIndex
   };

private:
   void setup();
   void dataFromInput(const Bytes& message);
   static void midiReceive(double timeStamp, std::vector<unsigned char>* message, void* userData);
   static void midiError(RtMidiError::Type type, const std::string& errorText, void* userData);

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   PolyRamp ramps[8];
   static const std::string keys;

   RtMidiIn midiInput;
   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;

   Range::Mapper cvMapper;
   SchweineSystem::LightMeter::List lightMeterList;
   SchweineSystem::Output::List outputList;

   SchweineSystem::LCDDisplay::Controller::List rampDisplayList;
   DisplayMode displayMode;
   SchweineSystem::Light::List displayModeLightList;
   dsp::BooleanTrigger displayTrigger;
   SchweineSystem::Color modeColors[3];

   SchweineSystem::LCDDisplay::Controller bankDisplay;
   uint8_t bankIndex;
   dsp::BooleanTrigger bankTrigger;
   bool receiveState;
   dsp::PulseGenerator applyPulse;
};

class TimeLordServerWidget : public ModuleWidget
{
public:
   TimeLordServerWidget(TimeLordServer* module);

private:
   SvgPanel* setup(TimeLordServer* module);
};

#endif // NOT TimeLordServerH
