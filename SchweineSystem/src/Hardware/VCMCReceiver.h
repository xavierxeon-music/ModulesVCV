#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>
#include <Tools/Counter.h>
#include <Tools/Range.h>

#include "SchweineSystemLCDDisplay.h"
#include "SchweineSystemLightMeter.h"

class VCMCReceiver : public Module
{
public:
   struct Panel;

public:
   VCMCReceiver();
   ~VCMCReceiver();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void processMessage(const midi::Message& msg);
   void connectToMidiDevice();

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   // tempo
   midi::InputQueue midiInput;
   Counter tickCounter;
   bool doNotAdvanceTempo;
   Tempo tempo;
   dsp::PulseGenerator clockTick;
   dsp::BooleanTrigger tickTrigger;
   dsp::BooleanTrigger tickOverrideTrigger;
   dsp::PulseGenerator clockReset;
   dsp::BooleanTrigger resetTrigger;
   SchweineSystem::Light connectionLight;
   SchweineSystem::LCDDisplay::Controller tempoDisplay;
   // gates
   bool gates[8];
   SchweineSystem::Light::List lightListGate;
   SchweineSystem::Output::List gateList;
   // cv
   uint8_t cvValues[8];
   SchweineSystem::LightMeter::List lightMeterListCV;
   SchweineSystem::Output::List cvOutputList;
   // sliders
   uint8_t sliderValues[8];
   SchweineSystem::LightMeter::List lightMeterListSlider;
   SchweineSystem::Output::List sliderOutputList;
   // general
   dsp::BooleanTrigger connectTrigger;
   Range::Mapper ccValueToVoltage;
};

class VCMCReceiverWidget : public ModuleWidget
{
public:
   VCMCReceiverWidget(VCMCReceiver* module);

private:
   SvgPanel* setup(VCMCReceiver* module);
};

#endif // NOT VCMCReceiverH
