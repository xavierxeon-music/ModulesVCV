#ifndef BitBusBitOutH
#define BitBusBitOutH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinCommon.h>
#include <SvinExpander.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinOutput.h>

class BitBusBitOut : public Svin::Module, public Svin::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusBitOut();
   ~BitBusBitOut();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

private:
   Svin::Output::List outputList;

   Svin::LED busInIndicator;
   Svin::LED busOutIndicator;
};

// widget

class BitBusBitOutWidget : public Svin::ModuleWidget
{
public:
   BitBusBitOutWidget(BitBusBitOut* module);

private:
   inline void setup();
};

#ifndef BitBusBitOutHPP
#include "BitBusBitOut.hpp"
#endif // NOT BitBusBitOutHPP

#endif // BitBusBitOutH
