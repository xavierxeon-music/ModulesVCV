#ifndef BefacoACDCH
#define BefacoACDCH

#include <rack.hpp>
using namespace rack;

#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinButtonLED.h>
#include <SvinLightMeter.h>
#include <SvinOutput.h>

class BefacoACDC : public Svin::Module, private Svin::Midi::Input
{
public:
   struct Panel;

public:
   BefacoACDC();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
   void connectToMidiDevice();
   void controllerChange(const Midi::Channel& channel, const Midi::ControllerMessage& controllerMessage, const uint8_t& value) override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::Output::List cvOutList;
   Svin::LightMeter::Controller::List cvMeterList;

   uint8_t ccValues[4];
   Range::Mapper ccValueToVoltage;

   Svin::ButtonLED connectionButton;
};

// widget

class BefacoACDCWidget : public Svin::ModuleWidget
{
public:
   BefacoACDCWidget(BefacoACDC* module);

private:
   inline void setup();
};

#ifndef BefacoACDCHPP
#include "BefacoACDC.hpp"
#endif // NOT BefacoACDCHPP

#endif // NOT BefacoACDCH
