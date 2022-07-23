#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>
#include <Tools/Counter.h>
#include <Tools/Range.h>

#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemLightMeter.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class VCMCReceiver : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   VCMCReceiver();
   ~VCMCReceiver();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup() override;
   void processMessage(const midi::Message& msg);
   void connectToMidiDevice();

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   // midi
   midi::InputQueue midiInput;
   dsp::BooleanTrigger connectTrigger;
   Range::Mapper ccValueToVoltage;
   SchweineSystem::LED connectionLight;
   // tempo
   Counter tickCounter;
   bool doNotAdvanceTempo;
   Tempo tempo;
   dsp::PulseGenerator clockTick;
   dsp::BooleanTrigger tickTrigger;
   dsp::PulseGenerator clockReset;
   dsp::BooleanTrigger resetTrigger;
   // gates
   bool gates[8];
   SchweineSystem::LED::List lightListGate;
   SchweineSystem::Output::List gateList;
   // cv
   uint8_t cvValues[8];
   SchweineSystem::LightMeter::Controller::List lightMeterListCV;
   SchweineSystem::Output::List cvOutputList;
   // sliders
   uint8_t sliderValues[8];
   SchweineSystem::LightMeter::Controller::List lightMeterListSlider;
   SchweineSystem::Output::List sliderOutputList;
};

class VCMCReceiverWidget : public SchweineSystem::ModuleWidget
{
public:
   VCMCReceiverWidget(VCMCReceiver* module);

private:
   void setup();
};

#endif // NOT VCMCReceiverH
