#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

#include <Tools/Range.h>

#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinOutput.h>

#include <SvinButtonLED.h>
#include <SvinLED.h>
#include <SvinLightMeter.h>

class VCMCReceiver : public Svin::Module
{
public:
   struct Panel;

public:
   VCMCReceiver();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void processMessage(const midi::Message& msg);
   void connectToMidiDevice();

private:
   // midi
   midi::InputQueue midiInput;
   Svin::ButtonLED connectionButton;
   Range::Mapper ccValueToVoltage;

   // gates
   bool gates[8];
   bool latches[8];
   Svin::Output gateOutput;
   Svin::LED::List gateLights;
   Svin::LED::List latchLights;

   // cv
   uint8_t cvValues[18]; // cv = 0-7, sliders = 8-15, A = 16, B = 17
   Svin::Output cvOutput;
   Svin::Output aOutput;
   Svin::Output bOutput;
   Svin::LightMeter::Controller::List cvMeter;
   Svin::LightMeter::Controller aMeter;
   Svin::LightMeter::Controller bMeter;
};

// widget

class VCMCReceiverWidget : public Svin::ModuleWidget
{
public:
   VCMCReceiverWidget(VCMCReceiver* module);

private:
   void setup();
};

#endif // NOT VCMCReceiverH
