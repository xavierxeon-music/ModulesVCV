#ifndef KeyStepChannelH
#define KeyStepChannelH

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

class KeyStepChannel : public SchweineSystem::Module, private SchweineSystem::MidiOutput
{
public:
   struct Panel;

public:
   KeyStepChannel();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void connectToMidiDevice();
   void sendProgramChange(uint8_t channel);
   void sendClockReset();
   void updateDisplay(uint8_t channel);

   void load(const SchweineSystem::Json::Object& rootObject) override;
   void save(SchweineSystem::Json::Object& rootObject) override;

private:
   // midi
   SchweineSystem::ButtonLED connectionButton;
   SchweineSystem::Switch midiChannelSwitch;
   // patterns
   SchweineSystem::Input::List inputList;
   uint8_t patterns[4];
   CvSwitch channelSwitch;
   // manual pattern
   SchweineSystem::DisplayLCD::Controller::List displayList;
   SchweineSystem::Button::List downButtonList;
   SchweineSystem::Button::List upButtonList;
   // manual reset
   dsp::BooleanTrigger resetTrigger;
};

class KeyStepChannelWidget : public SchweineSystem::ModuleWidget
{
public:
   KeyStepChannelWidget(KeyStepChannel* module);

private:
   void setup();
};

#endif // NOT KeyStepChannelH
