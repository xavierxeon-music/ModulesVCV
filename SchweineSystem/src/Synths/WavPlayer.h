#ifndef WavPlayerH
#define WavPlayerH

#include <rack.hpp>
using namespace rack;

#include <Sound/SampleOscilator.h>

#include <SyButton.h>
#include <SyButtonLED.h>
#include <SyDisplayOLED.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

class WavPlayer : public Sy::Module
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

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

   void onSampleRateChange(const SampleRateChangeEvent& event) override;

private:
   Sy::DisplayOLED::Controller displayController;
   Sample::Oscilator oscilator;
   float sampleRate;
   // file
   std::string fileName;
   // play
   bool play;
   Sy::ButtonLED playButton;
   // reset
   Sy::Button resetButton;
   // loop
   bool loop;
   Sy::ButtonLED loopButton;
};

// widget

class WavPlayerWidget : public Sy::ModuleWidget
{
public:
   WavPlayerWidget(WavPlayer* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);   
};

#endif // NOT WavPlayerH
