#ifndef BitBusMeterAndFreezeH
#define BitBusMeterAndFreezeH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SvinExapnder.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

#include <Tools/BoolField.h>
#include <Tools/RingBuffer.h>

#include <SvinCommon.h>
#include <SvinInput.h>
#include <SvinLED.h>

static constexpr uint16_t AverageBufferSize = 4800;

class BitBusMeterAndFreeze : public Svin::Module, public Svin::Exapnder<BitBusMessage>
{
public:
   struct Panel;

public:
   BitBusMeterAndFreeze();
   ~BitBusMeterAndFreeze();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void load(const Svin::Json::Object& rootObject) override;
   void save(Svin::Json::Object& rootObject) override;

private:
   Svin::LED::List lightList;
   dsp::BooleanTrigger freezTrigger;
   bool freezeMode;
   BoolField8 freezeBuffer;
   dsp::BooleanTrigger sampleTrigger;

   Svin::LED busInIndicator;
   Svin::LED busOutIndicator;
};

class BitBusMeterAndFreezeWidget : public Svin::ModuleWidget
{
public:
   BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module);

private:
   void setup();
};

#endif // NOT BitBusMeterAndFreezeH
