#ifndef GrooveMaestroH
#define GrooveMaestroH

#include <rack.hpp>
using namespace rack;

#include <SvinMasterClock.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Blocks/Contour.h>
#include <Blocks/Grooves.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>
#include <SvinSwitch.h>

class GrooveMaestro : public Svin::Module, public Svin::MasterClock::Client
{
public:
   struct Panel;

public:
   GrooveMaestro();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
};

// widget

class GrooveMaestroWidget : public Svin::ModuleWidget
{
public:
   GrooveMaestroWidget(GrooveMaestro* module);

private:
   inline void setup();
};

#ifndef GrooveMaestroHPP
#include "GrooveMaestro.hpp"
#endif // NOT GrooveMaestroHPP

#endif // NOT GrooveMaestroH
