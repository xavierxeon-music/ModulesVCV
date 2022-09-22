#ifndef NosferatuAcolyteH
#define NosferatuAcolyteH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinKnob.h>
#include <SvinLED.h>
#include <SvinSlider.h>

class NosferatuAcolyte : public Svin::Module
{
public:
   struct Panel;

public:
   NosferatuAcolyte();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

private:
   Svin::DisplayLCD::Controller display;
};

// widget

class NosferatuAcolyteWidget : public Svin::ModuleWidget
{
public:
   NosferatuAcolyteWidget(NosferatuAcolyte* module);

private:
   inline void setup();
};

#ifndef NosferatuAcolyteHPP
#include "NosferatuAcolyte.hpp"
#endif // NOT NosferatuAcolyteHPP

#endif // NOT NosferatuAcolyteH
