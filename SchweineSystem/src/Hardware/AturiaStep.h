#ifndef AturiaStepH
#define AturiaStepH

#include <rack.hpp>
using namespace rack;

#include <Blocks/CvSwitch.h>

#include <SchweineSystemButton.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>
#include <SchweineSystemSwitch.h>

#include "MidiBusModule.h"

class AturiaStep : public SchweineSystem::Module, public MidiBusModule
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

   void load(const SchweineSystem::Json::Object& rootObject) override;
   void save(SchweineSystem::Json::Object& rootObject) override;

private:
   // midi
   bool useDrumChannel;
   SchweineSystem::ButtonLED drumButon;
   SchweineSystem::ButtonLED connectionButton;
   // patterns
   SchweineSystem::Input::List inputList;
   uint8_t patterns[4];
   CvSwitch channelSwitch;
   // manual pattern
   SchweineSystem::DisplayLCD::Controller::List displayList;
   SchweineSystem::Button::List downButtonList;
   SchweineSystem::Button::List upButtonList;
};

// widget

class AturiaStepWidget : public SchweineSystem::ModuleWidget
{
public:
   AturiaStepWidget(AturiaStep* module);

private:
   void setup();
};

#endif // NOT AturiaStepH
