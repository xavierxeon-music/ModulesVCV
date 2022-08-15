#ifndef BitBusCVOutH
#define BitBusCVOutH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SchweineSystemCommon.h>
#include <SchweineSystemExapnder.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

class BitBusCVOut : public SchweineSystem::Module, public SchweineSystem::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusCVOut();
   ~BitBusCVOut();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   Range::Mapper outputMapper;

   SchweineSystem::LED busInIndicator;
};

class BitBusCVOutWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusCVOutWidget(BitBusCVOut* module);

private:
   void setup();
};

#endif // BitBusCVOutH
