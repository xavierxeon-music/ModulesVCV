#ifndef LinkControlH
#define LinkControlH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinLED.h>

class LinkControl : public Svin::Module
{
public:
   struct Panel;

public:
   LinkControl();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

private:
   Svin::LED::List noteList;
   Svin::LED connectedLight;
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
