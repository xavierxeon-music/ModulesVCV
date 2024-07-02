#ifndef ScaleShowH
#define ScaleShowH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinLED.h>
#include <SvinDisplayOLED.h>

class ScaleShow : public Svin::Module, public Svin::MasterClock::Client, public Svin::MidiOutput
{
public:
   struct Panel;

public:
   ScaleShow();

public:
   void process(const ProcessArgs& args) override;

private:
   enum class State
   {
      Play,
      Stop,
      Reset
   };

private:
   inline void setup();

   void updateDisplays() override;
   void sendStateToClock(const State& state);
   void playPausePressed(const float& x, const float& y);
   void resetPressed(const float& x, const float& y);

private:
   Svin::DisplayOLED::Controller playPauseController;
   bool isRunning;

   Svin::DisplayOLED::Controller resetController;

   Svin::LED connectedLight;
};

// widget

class ScaleShowWidget : public Svin::ModuleWidget
{
public:
   ScaleShowWidget(ScaleShow* module);

private:
   inline void setup();
};

#ifndef ScaleShowHPP
#include "ScaleShow.hpp"
#endif // NOT ScaleShowHPP

#endif // NOT ScaleShowH
