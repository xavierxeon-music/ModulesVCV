#ifndef MidiReplayH
#define MidiReplayH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Midi/MidiCommon.h>
#include <Midi/MidiFile.h>
#include <Music/TimeCode.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>


class MidiReplay : public Svin::Module, public Svin::MasterClock::Client
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

private:
   std::string fileName;
   Midi::Sequence midiReplay;
   Midi::Sequence::Info info;

   // display
   DisplayMode displayMode;
   Svin::Button pageButton;
   Svin::DisplayOLED::Controller displayController;

   // manual
   Svin::Input playInput;
   Svin::Input manualResetInput;
   Svin::Output endOutput;

   // cycle
   Svin::ButtonLED loopButton;
   bool isLooping;
   bool atEnd;
   dsp::PulseGenerator endPulse;

   // current position
   TimeCode::Duration duration;
   Midi::Sequence::Tick currentTick;
   Midi::Sequence::Tick lastTick;
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
