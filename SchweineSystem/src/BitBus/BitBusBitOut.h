#ifndef BitBusBitOutH
#define BitBusBitOutH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SchweineSystemCommon.h>
#include <SchweineSystemExapnder.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

class BitBusBitOut : public SchweineSystem::Module, public SchweineSystem::Exapnder<BitBusMessage>
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
   SchweineSystem::Output::List outputList;

   SchweineSystem::LED busInIndicator;
   SchweineSystem::LED busOutIndicator;
};

// widget

class BitBusBitOutWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusBitOutWidget(BitBusBitOut* module);

private:
   void setup();
};

#endif // BitBusBitOutH
