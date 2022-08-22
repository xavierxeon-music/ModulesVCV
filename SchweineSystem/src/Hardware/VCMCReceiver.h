#ifndef VCMCReceiverH
#define VCMCReceiverH

#include <rack.hpp>
using namespace rack;

#include <Tools/Counter.h>
#include <Tools/Range.h>

#include <SyButtonLED.h>
#include <SyDisplayLCD.h>
#include <SyLightMeter.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

class VCMCReceiver : public Sy::Module
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

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   // midi
   midi::InputQueue midiInput;
   Sy::ButtonLED connectionButton;
   Range::Mapper ccValueToVoltage;
   // gates
   bool gates[8];
   Sy::LED::List lightListGate;
   Sy::Output::List gateList;
   // sliders
   uint8_t sliderValues[8];
   Sy::LightMeter::Controller::List lightMeterListSlider;
   Sy::Output::List sliderOutputList;
   // cv
   uint8_t cvValues[10];
   Sy::LightMeter::Controller::List lightMeterListCV;
   Sy::Output::List cvOutputList;
};

class VCMCReceiverWidget : public Sy::ModuleWidget
{
public:
   VCMCReceiverWidget(VCMCReceiver* module);

private:
   void setup();
};

#endif // NOT VCMCReceiverH
