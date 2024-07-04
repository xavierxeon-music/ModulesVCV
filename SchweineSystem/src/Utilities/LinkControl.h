#ifndef LinkControlH
#define LinkControlH

#include <rack.hpp>
using namespace rack;

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

namespace ableton
{
   class Link;
}

class LinkControl : public Svin::Module
{
public:
   struct Panel;

public:
   LinkControl();
   ~LinkControl();

public:
   void process(const ProcessArgs& args) override;
   void updateDisplays() override;

private:
   inline void setup();

private:
   Svin::DisplayOLED::Controller displayController;
   Svin::ButtonLED playButton;
   Svin::Button tempoUpButton;
   Svin::Button tempoDownButton;

   ableton::Link* link;
};

// widget

class LinkControlWidget : public Svin::ModuleWidget
{
public:
   LinkControlWidget(LinkControl* module);

private:
   inline void setup();
};

#ifndef LinkControlHPP
#include "LinkControl.hpp"
#endif // NOT LinkControlHPP

#endif // NOT LinkControlH
