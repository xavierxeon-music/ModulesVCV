#ifndef BitBusMeterAndFreezeH
#define BitBusMeterAndFreezeH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"
#include <SyExapnder.h>
#include <SyModule.h>
#include <SyModuleWidget.h>

#include <Tools/BoolField.h>
#include <Tools/RingBuffer.h>

#include <SyCommon.h>
#include <SyLED.h>

static constexpr uint16_t AverageBufferSize = 4800;

class BitBusMeterAndFreeze : public Sy::Module, public Sy::Exapnder<BitBusMessage>
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

   void load(const Sy::Json::Object& rootObject) override;
   void save(Sy::Json::Object& rootObject) override;

private:
   Sy::LED::List lightList;
   dsp::BooleanTrigger freezTrigger;
   bool freezeMode;
   BoolField8 freezeBuffer;
   dsp::BooleanTrigger sampleTrigger;

   Sy::LED busInIndicator;
   Sy::LED busOutIndicator;
};

class BitBusMeterAndFreezeWidget : public Sy::ModuleWidget
{
public:
   BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module);

private:
   void setup();
};

#endif // NOT BitBusMeterAndFreezeH
