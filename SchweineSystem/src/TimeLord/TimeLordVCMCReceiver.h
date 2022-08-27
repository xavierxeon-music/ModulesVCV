#ifndef TimeLordVCMCReceiverH
#define TimeLordVCMCReceiverH

#include <rack.hpp>
using namespace rack;

#include <Tools/Counter.h>
#include <Tools/Range.h>

#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinLightMeter.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinOutput.h>

class TimeLordVCMCReceiver : public Svin::Module
{
public:
   struct Panel;

public:
   TimeLordVCMCReceiver();
   ~TimeLordVCMCReceiver();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void processMessage(const midi::Message& msg);
   void connectToMidiDevice();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   // midi
   midi::InputQueue midiInput;
   Svin::ButtonLED connectionButton;
   Range::Mapper ccValueToVoltage;
   // gates
   bool gates[8];
   Svin::LED::List lightListGate;
   Svin::Output::List gateList;
   // sliders
   uint8_t sliderValues[8];
   Svin::LightMeter::Controller::List lightMeterListSlider;
   Svin::Output::List sliderOutputList;
   // cv
   uint8_t cvValues[10];
   Svin::LightMeter::Controller::List lightMeterListCV;
   Svin::Output::List cvOutputList;
};

class TimeLordVCMCReceiverWidget : public Svin::ModuleWidget
{
public:
   TimeLordVCMCReceiverWidget(TimeLordVCMCReceiver* module);

private:
   void setup();
};

#endif // NOT TimeLordVCMCReceiverH
