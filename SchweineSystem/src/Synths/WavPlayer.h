#ifndef WavPlayerH
#define WavPlayerH

#include <rack.hpp>
using namespace rack;

#include <Sound/SampleOscilator.h>

#include <SchweineSystemButton.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

class WavPlayer : public SchweineSystem::Module
{
public:
   struct Panel;

public:
   WavPlayer();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;
   void setWavFileName(const std::string& newFileName);

private:
   void setup();
   void load();
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;
   void onSampleRateChange(const SampleRateChangeEvent& event) override;

private:
   SchweineSystem::DisplayOLED::Controller displayController;
   Sample::Oscilator oscilator;
   float sampleRate;

   // file
   std::string fileName;

   // play
   bool play;
   SchweineSystem::ButtonLED playButton;
   // reset
   SchweineSystem::Button resetButton;
   // loop
   bool loop;
   SchweineSystem::ButtonLED loopButton;
};

// widget

class WavPlayerWidget : public SchweineSystem::ModuleWidget
{
public:
   WavPlayerWidget(WavPlayer* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);   
};

#endif // NOT WavPlayerH
