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
   inline void setup();
   void load();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

   void onSampleRateChange(const SampleRateChangeEvent& event) override;

private:
   Svin::DisplayOLED::Controller displayController;
   // file
   Sample::Oscilator oscilator;
   float sampleRate;
   std::string fileName;

   // play
   Svin::ButtonLED playButton;
   Svin::Input playInput;

   // reset
   Svin::Button resetButton;
   Svin::Input resetInput;

   // loop
   Svin::ButtonLED loopButton;
   Svin::Input loopInput;

   Svin::Input pitchInput;

   Svin::Output polyOutput;
   Svin::Output rightOutput;
};

// widget

class WavPlayerWidget : public Svin::ModuleWidget
{
public:
   WavPlayerWidget(WavPlayer* module);

private:
   inline void setup();
};

#ifndef WavPlayerHPP
#include "WavPlayer.hpp"
#endif // NOT WavPlayerHPP

#endif // NOT WavPlayerH
