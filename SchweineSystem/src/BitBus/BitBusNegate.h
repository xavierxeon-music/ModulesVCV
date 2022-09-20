#ifndef BitBusNegateH
#define BitBusNegateH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinButtonLED.h>
#include <SvinCommon.h>
#include <SvinExpander.h>
#include <SvinInput.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

class BitBusNegate : public Svin::Module, public Svin::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusNegate();
   ~BitBusNegate();

public:
   void process(const ProcessArgs& args) override;

private:
   inline void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::ButtonLED::List latchList;
   Svin::Input::List gateList;

   Svin::LED busInIndicator;
   Svin::LED busOutIndicator;
};

// widget

class BitBusNegateWidget : public Svin::ModuleWidget
{
public:
   BitBusNegateWidget(BitBusNegate* module);

private:
   inline void setup();
};

#ifndef BitBusNegateHPP
#include "BitBusNegate.hpp"
#endif // NOT BitBusNegateHPP

#endif // NOT BitBusNegateH
