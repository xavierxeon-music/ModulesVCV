#ifndef BitBusBitInH
#define BitBusBitInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyCommon.h>
#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

#include <SyLED.h>

class BitBusBitIn : public Sy::Module, public Sy::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusBitIn();
   ~BitBusBitIn();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   Sy::Input::List inputList;

   Sy::LED busInIndicator;
   Sy::LED busOutIndicator;
};

class BitBusBitInWidget : public Sy::ModuleWidget
{
public:
   BitBusBitInWidget(BitBusBitIn* module);

private:
   void setup();
};

#endif // BitBusBitInH
