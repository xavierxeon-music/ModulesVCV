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
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class MidiReplay : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   MidiReplay();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

   void loadMidiFile(const std::string& newFileName);

   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   enum class DisplayMode
   {
      Overview,
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
   SchweineSystem::Button displayButton;
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
