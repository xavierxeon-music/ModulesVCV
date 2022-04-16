#ifndef BitBusMeterAndFreezeH
#define BitBusMeterAndFreezeH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

#include <Tools/BoolField.h>
#include <Tools/RingBuffer.h>

#include "SchweineSystemLightMeter.h"

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
   class Average
   {
   public:
      using List = Average[8];

   public:
      Average();

   public:
      uint16_t observe(const bool value);

   private:
      RingBuffer<bool, AverageBufferSize> buffer;
      uint16_t sum;
   };

private:
   void setup();

   void onAdd(const AddEvent& e) override;
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   Average::List averageList;
   SchweineSystem::LightMeter::List lightMeterList;
   dsp::BooleanTrigger freezTrigger;
   bool freezeMode;
   BoolField8 freezeBuffer;
   dsp::BooleanTrigger sampleTrigger;     
};

struct BitBusMeterAndFreezeWidget : ModuleWidget
{
   BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module);
};

#endif // NOT BitBusMeterAndFreezeH
