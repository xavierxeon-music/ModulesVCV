#ifndef BitBusTransmutorH
#define BitBusTransmutorH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinButton.h>
#include <SvinDisplayOLED.h>
#include <SvinExapnder.h>
#include <SvinLED.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Sound/WaveTable.h>
#include <Tools/Range.h>

class BitBusTransmutor : public Svin::Module, public Svin::Exapnder<BitBusMessage>
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

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::Button displayButton;
   Svin::DisplayOLED::Controller displayController;

   Svin::LED busInIndicator;
   Svin::LED busOutIndicator;

   Range::Mapper inputMapper;
   WaveTable::StepValueTable* table;
};

// widget

class BitBusTransmutorWidget : public Svin::ModuleWidget
{
public:
   BitBusTransmutorWidget(BitBusTransmutor* module);

private:
   void setup();
};

#endif // NOT BitBusTransmutorH
