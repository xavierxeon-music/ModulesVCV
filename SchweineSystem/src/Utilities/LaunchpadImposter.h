#ifndef LaunchpadImposterH
#define LaunchpadImposterH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinButtonLED.h>
#include <SvinLED.h>

class LaunchpadImposter : public Svin::Module
{
public:
   struct Panel;

public:
   LaunchpadImposter();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
};

// widget

class LaunchpadImposterWidget : public Svin::ModuleWidget
{
public:
   LaunchpadImposterWidget(LaunchpadImposter* module);

private:
   inline void setup();
};

#ifndef LaunchpadImposterHPP
#include "LaunchpadImposter.hpp"
#endif // NOT LaunchpadImposterHPP

#endif // NOT LaunchpadImposterH
