#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

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

private:
   SchweineSystem::LightMeter::List lightMeterListCV;
   SchweineSystem::LightMeter::List lightMeterListSlider;
   SchweineSystem::Light::List lightListGate;

   dsp::BooleanTrigger downTrigger;
   dsp::BooleanTrigger upTrigger;
};

class VCMCReceiverWidget : public ModuleWidget
{
public:
   VCMCReceiverWidget(VCMCReceiver* module);

private:
   SvgPanel* setup(VCMCReceiver* module);
};

#endif // NOT VCMCReceiverH
