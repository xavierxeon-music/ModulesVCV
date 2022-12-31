#ifndef HubConnectH
#define HubConnectH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinDisplayOLED.h>
#include <SvinLED.h>

class HubConnect : public Svin::Module, private Svin::MasterClock::Client
{
public:
   struct Panel;

public:
   HubConnect();

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
   Svin::LED::List noteList;
   Svin::LED connectedLight;
};

// widget

class HubConnectWidget : public Svin::ModuleWidget
{
public:
   HubConnectWidget(HubConnect* module);

private:
   inline void setup();
};

#ifndef HubConnectHPP
#include "HubConnect.hpp"
#endif // NOT HubConnectHPP

#endif // NOT HubConnectH
