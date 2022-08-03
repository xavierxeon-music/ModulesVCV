#ifndef MidiReplayH
#define MidiReplayH

#include <rack.hpp>
using namespace rack;

#include <Midi/MidiFileReader.h>
#include <Music/Tempo.h>

#include <SchweineSystemButton.h>
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
   Midi::FileReader midiReplay;
   Replay::Info info;

   // display
   DisplayMode displayMode;
   SchweineSystem::Button displayButton;
   SchweineSystem::DisplayOLED::Controller displayController;

   // clock
   dsp::BooleanTrigger clockTrigger;
   dsp::BooleanTrigger resetTrigger;
   Tempo tempo;
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
