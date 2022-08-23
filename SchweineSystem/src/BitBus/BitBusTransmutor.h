#ifndef BitBusTransmutorH
#define BitBusTransmutorH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyButton.h>
#include <SyDisplayOLED.h>
#include <SyExapnder.h>
#include <SyLED.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

class BitBusTransmutor : public Sy::Module, public Sy::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusTransmutor();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void updateDisplays() override;

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   Sy::Button displayButton;
   Sy::DisplayOLED::Controller displayController;

   Sy::LED busInIndicator;
   Sy::LED busOutIndicator;
};

// widget

class BitBusTransmutorWidget : public Sy::ModuleWidget
{
public:
   BitBusTransmutorWidget(BitBusTransmutor* module);

private:
   void setup();
};

#endif // NOT BitBusTransmutorH
