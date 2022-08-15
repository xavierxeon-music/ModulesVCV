#ifndef BitBusCVInH
#define BitBusCVInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SchweineSystemExapnder.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

class BitBusCVIn : public SchweineSystem::Module, public SchweineSystem::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusCVIn();
   ~BitBusCVIn();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   Range::Mapper inputMapper;

   SchweineSystem::LED busOutIndicator;
};

// widget

class BitBusCVInWidget : public SchweineSystem::ModuleWidget
{
public:
   BitBusCVInWidget(BitBusCVIn* module);

private:
   void setup();
};

#endif // BitBusCVInH
