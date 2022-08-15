#ifndef BitBusBitInH
#define BitBusBitInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SchweineSystemCommon.h>
#include <SchweineSystemExapnder.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <SchweineSystemLED.h>

class BitBusBitIn : public SchweineSystem::Module, public SchweineSystem::Exapnder<BitBusMessage>
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
   SchweineSystem::Input::List inputList;

   SchweineSystem::LED busInIndicator;
   SchweineSystem::LED busOutIndicator;
};

class BitBusBitInWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusBitInWidget(BitBusBitIn* module);

private:
   void setup();
};

#endif // BitBusBitInH
