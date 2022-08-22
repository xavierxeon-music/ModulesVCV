#ifndef MidiReplayH
#define MidiReplayH

#include <rack.hpp>
using namespace rack;

#include <Blocks/Sequencer.h>
#include <Midi/MidiCommon.h>
#include <Midi/MidiFile.h>
#include <Music/Tempo.h>
#include <Music/TimeCode.h>

#include <SyButton.h>
#include <SyButtonLED.h>
#include <SyDisplayOLED.h>
#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

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

class MidiReplay : public Sy::Module, public Sy::Exapnder<BusMidi>
{
public:
   struct Panel;

public:
   MidiReplay();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

   void loadMidiFile(const std::string& newFileName);

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

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
   Sy::Button pageButton;
   Sy::DisplayOLED::Controller displayController;

   // clock
   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;

   // cycle
   Sy::ButtonLED loopButton;
   bool isLooping;
   bool atEnd;
   dsp::PulseGenerator endPulse;

   // current position
   TimeCode::Duration duration;
   Sequencer::Tick currentTick;
   Sequencer::Tick lastTick;
};

// widget

class MidiReplayWidget : public Sy::ModuleWidget
{
public:
   MidiReplayWidget(MidiReplay* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);
};

#endif // NOT MidiReplayH
