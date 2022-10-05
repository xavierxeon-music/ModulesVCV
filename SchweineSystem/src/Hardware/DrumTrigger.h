#ifndef DrumTriggerH
#define DrumTriggerH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinInput.h>

class DrumTrigger : public Svin::Module
{
public:
   struct Panel;

public:
   DrumTrigger();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
};

// widget

class DrumTriggerWidget : public Svin::ModuleWidget
{
public:
   DrumTriggerWidget(DrumTrigger* module);

private:
   inline void setup();
};

#ifndef DrumTriggerHPP
#include "DrumTrigger.hpp"
#endif // NOT DrumTriggerHPP

#endif // NOT DrumTriggerH
