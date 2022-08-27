#ifndef BitBusBitInH
#define BitBusBitInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinCommon.h>
#include <SvinExapnder.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

class BitBusBitIn : public Svin::Module, public Svin::Exapnder<BitBusMessage>
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
   Svin::Input::List inputList;

   Svin::LED busInIndicator;
   Svin::LED busOutIndicator;
};

class BitBusBitInWidget : public Svin::ModuleWidget
{
public:
   BitBusBitInWidget(BitBusBitIn* module);

private:
   void setup();
};

#endif // BitBusBitInH
