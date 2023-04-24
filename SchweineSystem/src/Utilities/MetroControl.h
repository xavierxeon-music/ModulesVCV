#ifndef MetroControlH
#define MetroControlH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinLED.h>
#include <SvinDisplayOLED.h>

class MetroControl : public Svin::Module, public Svin::MasterClock::Client
{
public:
   struct Panel;

public:
   MetroControl();

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
};

// widget

class MetroControlWidget : public Svin::ModuleWidget
{
public:
   MetroControlWidget(MetroControl* module);

private:
   inline void setup();
};

#ifndef MetroControlHPP
#include "MetroControl.hpp"
#endif // NOT MetroControlHPP

#endif // NOT MetroControlH
