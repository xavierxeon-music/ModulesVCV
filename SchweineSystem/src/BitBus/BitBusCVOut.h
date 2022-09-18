#ifndef BitBusCVOutH
#define BitBusCVOutH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinCommon.h>
#include <SvinExapnder.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinCommon.h>
#include <SvinLED.h>
#include <SvinOutput.h>

class BitBusCVOut : public Svin::Module, public Svin::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusCVOut();
   ~BitBusCVOut();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

private:
   Svin::Output cvOutput;
   Range::Mapper outputMapper;

   Svin::LED busInIndicator;
};

class BitBusCVOutWidget : public Svin::ModuleWidget
{
public:
   BitBusCVOutWidget(BitBusCVOut* module);

private:
   inline void setup();
};

#ifndef BitBusCVOutHPP
#include "BitBusCVOut.hpp"
#endif // NOT BitBusCVOutHPP

#endif // BitBusCVOutH
