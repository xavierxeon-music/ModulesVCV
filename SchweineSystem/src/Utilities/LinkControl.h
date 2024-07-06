#ifndef LinkControlH
#define LinkControlH

#include <rack.hpp>
using namespace rack;

#include <ableton/Link.hpp>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinLightMeter.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

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
   ableton::Link link;

   Svin::DisplayLCD::Controller tempoDisplay;
   Svin::Button tempoUpHundredButton;
   Svin::Button tempoDownHundredButton;
   Svin::Button tempoUpTenButton;
   Svin::Button tempoDownTenButton;
   Svin::Button tempoUpOneButton;
   Svin::Button tempoDownOneButton;

   Svin::ButtonLED playButton;
   Svin::LightMeter::Controller syncMeter;
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
