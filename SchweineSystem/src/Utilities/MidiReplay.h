#ifndef MidiReplayH
#define MidiReplayH

#include <rack.hpp>
using namespace rack;

#include <Midi/MidiFile.h>
#include <Music/Tempo.h>
#include <Music/TimeCode.h>

#include <SchweineSystemButton.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemExapnder.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemExpanderMessages.h>

class MidiReplay : public SchweineSystem::Module, public SchweineSystem::Exapnder<SchweineSystem::BusMidi>
{
public:
   struct Panel;

public:
   MidiReplay();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

   void loadMidiFile(const std::string& newFileName);

   void load(const SchweineSystem::Json::Object& rootObject) override;
   void save(SchweineSystem::Json::Object& rootObject) override;

private:
   enum class DisplayMode
   {
      Overview,
      Tracks,
      Current
   };

private:
   void setup();

private:
   std::string fileName;
   Sequencer midiReplay;
   Sequencer::Info info;

   // display
   DisplayMode displayMode;
   SchweineSystem::Button pageButton;
   SchweineSystem::Button editUpButton;
   SchweineSystem::Button editDownButton;
   SchweineSystem::Button editLeftButton;
   SchweineSystem::Button editRightButton;
   SchweineSystem::DisplayOLED::Controller displayController;

   // clock
   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;

   // cycle
   SchweineSystem::ButtonLED loopButton;
   bool isLooping;
   bool atEnd;
   dsp::PulseGenerator endPulse;

   // current position
   TimeCode::Duration duration;
   Sequencer::Tick currentTick;
   Sequencer::Tick lastTick;
};

// widget

class MidiReplayWidget : public SchweineSystem::ModuleWidget
{
public:
   MidiReplayWidget(MidiReplay* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);
};

#endif // NOT MidiReplayH
