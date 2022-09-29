#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinButtonLED.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinLightMeter.h>
#include <SvinOutput.h>

class VCMCReceiver : public Svin::Module, public Svin::Midi::Input
{
public:
   struct Panel;

public:
   VCMCReceiver();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
   void connectToMidiDevice();
   void noteOn(const Midi::Channel& channel, const Note& note, const Midi::Velocity& velocity) override;
   void controllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   // midi
   Svin::ButtonLED connectionButton;
   Range::Mapper ccValueToVoltage;

   // gates
   bool gates[8];
   bool latches[8];
   Svin::Output gateOutput;
   Svin::LED::List gateLights;
   Svin::LED::List latchLights;
   Svin::Input latchReset;

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
   inline void setup();
};

#ifndef VCMCReceiverHPP
#include "VCMCReceiver.hpp"
#endif // NOT VCMCReceiverHPP

#endif // NOT VCMCReceiverH
