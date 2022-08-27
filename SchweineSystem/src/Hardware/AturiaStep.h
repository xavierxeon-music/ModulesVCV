#ifndef AturiaStepH
#define AturiaStepH

#include <rack.hpp>
using namespace rack;

#include <Blocks/CvSwitch.h>

#include "MidiBusModule.h"
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinSwitch.h>

class AturiaStep : public Svin::Module, public MidiBusModule
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

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   // midi
   bool useDrumChannel;
   Svin::ButtonLED drumButon;
   Svin::ButtonLED connectionButton;
   // patterns
   Svin::Input::List inputList;
   uint8_t patterns[4];
   CvSwitch channelSwitch;
   // manual pattern
   Svin::DisplayLCD::Controller::List displayList;
   Svin::Button::List downButtonList;
   Svin::Button::List upButtonList;
};

// widget

class AturiaStepWidget : public Svin::ModuleWidget
{
public:
   AturiaStepWidget(AturiaStep* module);

private:
   void setup();
};

#endif // NOT AturiaStepH
