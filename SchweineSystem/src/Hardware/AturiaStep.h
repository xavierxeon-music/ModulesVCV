#ifndef AturiaStepH
#define AturiaStepH

#include <rack.hpp>
using namespace rack;

#include <Blocks/CvSwitch.h>

#include <SyButton.h>
#include <SyButtonLED.h>
#include <SyDisplayLCD.h>
#include <SyModule.h>
#include <SyModuleWidget.h>
#include <SySwitch.h>

#include "MidiBusModule.h"

class AturiaStep : public Sy::Module, public MidiBusModule
{
public:
   struct Panel;

public:
   AturiaStep();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();
   void sendProgramChange(uint8_t channel);
   void updateDisplay(uint8_t channel);

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   // midi
   bool useDrumChannel;
   Sy::ButtonLED drumButon;
   Sy::ButtonLED connectionButton;
   // patterns
   Sy::Input::List inputList;
   uint8_t patterns[4];
   CvSwitch channelSwitch;
   // manual pattern
   Sy::DisplayLCD::Controller::List displayList;
   Sy::Button::List downButtonList;
   Sy::Button::List upButtonList;
};

// widget

class AturiaStepWidget : public Sy::ModuleWidget
{
public:
   AturiaStepWidget(AturiaStep* module);

private:
   void setup();
};

#endif // NOT AturiaStepH
