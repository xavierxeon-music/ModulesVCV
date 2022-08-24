#ifndef BitBusBitOutH
#define BitBusBitOutH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyCommon.h>
#include <SyExapnder.h>
#include <SyLED.h>
#include <SyModule.h>
#include <SyModuleWidget.h>
#include <SyOutput.h>

class BitBusBitOut : public Sy::Module, public Sy::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusBitOut();
   ~BitBusBitOut();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   Sy::Output::List outputList;

   Sy::LED busInIndicator;
   Sy::LED busOutIndicator;
};

// widget

class BitBusBitOutWidget : public Sy::ModuleWidget
{
public:
   BitBusBitOutWidget(BitBusBitOut* module);

private:
   void setup();
};

#endif // BitBusBitOutH
