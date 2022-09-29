#ifndef GateKeeperH
#define GateKeeperH

#include <rack.hpp>
using namespace rack;

#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinSwitch.h>
#include <SvinInput.h>
#include <SvinOutput.h>

class GateKeeper : public Svin::Module
{
public:
   struct Panel;

public:
   GateKeeper();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();
};

// widget

class GateKeeperWidget : public Svin::ModuleWidget
{
public:
   GateKeeperWidget(GateKeeper* module);

private:
   inline void setup();
};

#ifndef GateKeeperHPP
#include "GateKeeper.hpp"
#endif // NOT GateKeeperHPP

#endif // NOT GateKeeperH
