#ifndef WavPlayerH
#define WavPlayerH

#include <rack.hpp>
using namespace rack;

#include <Sound/SampleOscilator.h>

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class WavPlayer : public Svin::Module
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

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

   void onSampleRateChange(const SampleRateChangeEvent& event) override;
   void displayClicked(const float& x, const float& y);

private:
   Svin::DisplayOLED::Controller displayController;
   Sample::Oscilator oscilator;
   float sampleRate;
   // file
   std::string fileName;
   // play
   bool play;
   Svin::ButtonLED playButton;
   // reset
   Svin::Button resetButton;
   // loop
   bool loop;
   Svin::ButtonLED loopButton;
};

// widget

class WavPlayerWidget : public Svin::ModuleWidget
{
public:
   WavPlayerWidget(WavPlayer* module);

private:
   void setup();
   void displayClicked(const float& x, const float& y);
};

#endif // NOT WavPlayerH
