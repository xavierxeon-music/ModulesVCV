#ifndef LaunchpadH
#define LaunchpadH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinButtonLED.h>
#include <SvinLED.h>

class Launchpad : public Svin::Module
{
public:
   struct Panel;

public:
   Launchpad();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
};

// widget

class LaunchpadWidget : public Svin::ModuleWidget
{
public:
   LaunchpadWidget(Launchpad* module);

private:
   inline void setup();
};

#ifndef LaunchpadHPP
#include "Launchpad.hpp"
#endif // NOT LaunchpadHPP

#endif // NOT LaunchpadH
