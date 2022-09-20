#ifndef BitBusCVInH
#define BitBusCVInH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinExpander.h>
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
   inline void setup();

private:
   Svin::Input cvInput;
   Range::Mapper inputMapper;

   Svin::LED busOutIndicator;
};

// widget

class BitBusCVInWidget : public Svin::ModuleWidget
{
public:
   BitBusCVInWidget(BitBusCVIn* module);

private:
   inline void setup();
};

#ifndef BitBusCVInHPP
#include "BitBusCVIn.hpp"
#endif // NOT BitBusCVInHPP

#endif // BitBusCVInH
