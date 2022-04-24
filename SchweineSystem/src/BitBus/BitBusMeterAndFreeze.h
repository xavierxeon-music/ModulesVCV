#ifndef BitBusMeterAndFreezeH
#define BitBusMeterAndFreezeH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

#include <Tools/BoolField.h>
#include <Tools/RingBuffer.h>

#include "SchweineSystemLight.h"

static constexpr uint16_t AverageBufferSize = 4800;

class BitBusMeterAndFreeze : public Module, public BitBusCommon
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

   void onAdd(const AddEvent& e) override;
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   SchweineSystem::Light::List lightList;
   dsp::BooleanTrigger freezTrigger;
   bool freezeMode;
   BoolField8 freezeBuffer;
   dsp::BooleanTrigger sampleTrigger;     
};

class BitBusMeterAndFreezeWidget : public ModuleWidget
{
public:
   BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module);

private:
   SvgPanel* setup(BitBusMeterAndFreeze* module);
};

#endif // NOT BitBusMeterAndFreezeH
