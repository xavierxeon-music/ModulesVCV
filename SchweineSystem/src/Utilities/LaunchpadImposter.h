#ifndef LaunchpadImposterH
#define LaunchpadImposterH

#include <rack.hpp>
using namespace rack;

#include <SvinMidi.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinButtonLED.h>
#include <SvinLED.h>

class LaunchpadImposter : public Svin::Module, private Svin::Midi::Input, private Svin::Midi::Output
{
public:
   struct Panel;

public:
   LaunchpadImposter();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

   void updateDisplays() override;

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   // id
   uint8_t deviceId;
   Svin::DisplayLCD::Controller deviceIdDisplay;
   Svin::Button deviceIdUpButton;
   Svin::Button deviceIdDownButton;

   Svin::ButtonLED::List buttonList;
   Svin::LED statusLED;
   std::map<uint8_t, uint8_t> indexToMidiNote;
   std::map<uint8_t, uint8_t> midiNoteToIndex;
};

// widget

class LaunchpadImposterWidget : public Svin::ModuleWidget
{
public:
   LaunchpadImposterWidget(LaunchpadImposter* module);

private:
   inline void setup();
};

#ifndef LaunchpadImposterHPP
#include "LaunchpadImposter.hpp"
#endif // NOT LaunchpadImposterHPP

#endif // NOT LaunchpadImposterH
