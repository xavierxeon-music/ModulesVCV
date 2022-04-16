#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

#include <Music/Tempo.h>
#include <Tools/Counter.h>

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

public:
   uint16_t bpm;

private:
   void setup();
   void processMessage(const midi::Message& msg);
   void connectToMidiDevice();

private:
   SchweineSystem::LightMeter::List lightMeterListCV;
   SchweineSystem::LightMeter::List lightMeterListSlider;
   SchweineSystem::Light::List lightListGate;
   SchweineSystem::Light connectionLight;
   midi::InputQueue midiInput;
   // tempo
   uint8_t midiTickCounter;
   bool doNotAdvanceTempo;
   Tempo tempo;
   dsp::PulseGenerator clockTick;
   dsp::PulseGenerator clockReset;
};

class VCMCReceiverWidget : public ModuleWidget
{
public:
   VCMCReceiverWidget(VCMCReceiver* module);

private:
   SvgPanel* setup(VCMCReceiver* module);
};

#endif // NOT VCMCReceiverH
