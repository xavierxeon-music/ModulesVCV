#ifndef HubConnectH
#define HubConnectH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinLED.h>

class HubConnect : public Svin::Module
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
   void sendStateToClock(const State& state);

private:
   Svin::LED::List noteList;
   Svin::Button playButton;
   Svin::Button stopButton;
   Svin::Button resetButton;
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
