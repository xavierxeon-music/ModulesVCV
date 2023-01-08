#ifndef MingleH
#define MingleH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButtonLED.h>
#include <SvinLED.h>
#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class Mingle : public Svin::Module
{
public:
   struct Panel;

public:
   Mingle();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
};

// widget

class MingleWidget : public Svin::ModuleWidget
{
public:
   MingleWidget(Mingle* module);

private:
   inline void setup();
};

#ifndef MingleHPP
#include "Mingle.hpp"
#endif // NOT MingleHPP

#endif // NOT MingleH
