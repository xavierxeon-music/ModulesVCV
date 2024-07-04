#ifndef LinkControlH
#define LinkControlH

#include <rack.hpp>
using namespace rack;

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
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

private:
   inline void setup();

private:
   Svin::LED::List noteList;
   Svin::LED connectedLight;

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
