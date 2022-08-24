#ifndef BitBusCVOutH
#define BitBusCVOutH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyCommon.h>
#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

#include <Tools/Range.h>

#include <SyCommon.h>
#include <SyLED.h>
#include <SyOutput.h>

class BitBusCVOut : public Sy::Module, public Sy::Exapnder<BitBusMessage>
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

   Sy::LED busInIndicator;
};

class BitBusCVOutWidget : public Sy::ModuleWidget
{
public:
   BitBusCVOutWidget(BitBusCVOut* module);

private:
   void setup();
};

#endif // BitBusCVOutH
