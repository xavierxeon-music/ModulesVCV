#ifndef KeyStepH
#define KeyStepH

#include <rack.hpp>
using namespace rack;

#include <Blocks/CvSwitch.h>

#include <SchweineSystemButton.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemCommon.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemMidiOutput.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>
#include <SchweineSystemSwitch.h>

class KeyStep : public SchweineSystem::Module, private SchweineSystem::MidiOutput
{
public:
   struct Panel;

public:
   KeyStep();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();
   void sendProgramChange(uint8_t channel);
   void updateDisplay(uint8_t channel);

private:
   // midi
   SchweineSystem::ButtonLED connect;
   SchweineSystem::Switch midiChannelSwitch;
   // patterns
   SchweineSystem::Input::List inputList;
   uint8_t patterns[4];
   CvSwitch channelSwitch;
   // manual pattern
   SchweineSystem::DisplayLCD::Controller::List displayList;
   SchweineSystem::Button::List downButtonList;
   SchweineSystem::Button::List upButtonList;
};

class KeyStepWidget : public SchweineSystem::ModuleWidget
{
public:
   KeyStepWidget(KeyStep* module);

private:
   void setup();
};

#endif // NOT KeyStepH
