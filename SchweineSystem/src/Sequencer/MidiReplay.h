#ifndef MidiReplayH
#define MidiReplayH

#include <rack.hpp>
using namespace rack;

#include <Blocks/Sequencer.h>
#include <Midi/MidiCommon.h>
#include <Midi/MidiFile.h>
#include <Music/Tempo.h>
#include <Music/TimeCode.h>

#include <SvinExapnder.h>
#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct BusMidi
{
   struct Channel
   {
      Sequencer::Track::NoteEvent::TimeMap noteOffEventMap;
      Sequencer::Track::NoteEvent::TimeMap noteOnEventMap;
      bool isMonophoic = false;
   };

   Sequencer::Tick startTick = 0;
   Sequencer::Tick endTick = 0;
   Tempo::RunState runState = Tempo::Reset;
   bool hasEvents = false;

   uint8_t noOfChannels = 0;
   Channel channels[16];
};

class MidiReplay : public Svin::Module, public Svin::Exapnder<BusMidi>, public Svin::MasterClock::Client
{
public:
   struct Panel;

public:
   MidiReplay();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

   void loadMidiFile(const std::string& newFileName);

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   enum class DisplayMode
   {
      Overview,
      Tracks,
      Current
   };

private:
   inline void setup();
   void displayClicked(const float& x, const float& y);

private:
   std::string fileName;
   Sequencer midiReplay;
   Sequencer::Info info;

   // display
   DisplayMode displayMode;
   Svin::Button pageButton;
   Svin::DisplayOLED::Controller displayController;

   // manual
   Svin::Input manualResetInput;

   // cycle
   Svin::ButtonLED loopButton;
   bool isLooping;
   bool atEnd;
   dsp::PulseGenerator endPulse;

   // current position
   TimeCode::Duration duration;
   Sequencer::Tick currentTick;
   Sequencer::Tick lastTick;
};

// widget

class MidiReplayWidget : public Svin::ModuleWidget
{
public:
   MidiReplayWidget(MidiReplay* module);

private:
   inline void setup();
};

#ifndef MidiReplayHPP
#include "MidiReplay.hpp"
#endif // NOT MidiReplayHPP

#endif // NOT MidiReplayH
