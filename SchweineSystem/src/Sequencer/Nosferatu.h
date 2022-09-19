#ifndef NosferatuH
#define NosferatuH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinKnob.h>
#include <SvinLED.h>
#include <SvinOutput.h>
#include <SvinSlider.h>
#include <SvinSwitch.h>

class Nosferatu : public Svin::Module
{
public:
   struct Panel;

public:
   Nosferatu();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
};

// widget

class NosferatuWidget : public Svin::ModuleWidget
{
public:
   NosferatuWidget(Nosferatu* module);

private:
   inline void setup();
};

#ifndef NosferatuHPP
#include "Nosferatu.hpp"
#endif // NOT NosferatuHPP

#endif // NOT NosferatuH
