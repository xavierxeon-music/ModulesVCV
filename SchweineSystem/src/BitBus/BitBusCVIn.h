#ifndef BitBusCVInH
#define BitBusCVInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

#include <Tools/Range.h>

#include <SyCommon.h>
#include <SyLED.h>

class BitBusCVIn : public Sy::Module, public Sy::Exapnder<BitBusMessage>
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

   Sy::LED busOutIndicator;
};

// widget

class BitBusCVInWidget : public Sy::ModuleWidget
{
public:
   BitBusCVInWidget(BitBusCVIn* module);

private:
   void setup();
};

#endif // BitBusCVInH
