#ifndef BitBusCVInH
#define BitBusCVInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinExapnder.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/Range.h>

#include <SvinCommon.h>
#include <SvinInput.h>
#include <SvinLED.h>

class BitBusCVIn : public Svin::Module, public Svin::Exapnder<BitBusMessage>
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

   Svin::LED busOutIndicator;
};

// widget

class BitBusCVInWidget : public Svin::ModuleWidget
{
public:
   BitBusCVInWidget(BitBusCVIn* module);

private:
   void setup();
};

#endif // BitBusCVInH
