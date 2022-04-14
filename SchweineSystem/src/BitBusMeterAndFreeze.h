#ifndef BitBusMeterAndFreezeH
#define BitBusMeterAndFreezeH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

#include <Tools/BoolField.h>
#include <Tools/RingBuffer.h>

class BitBusMeterAndFreeze : public Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusMeterAndFreeze();
   ~BitBusMeterAndFreeze();

public:
   void process(const ProcessArgs& args) override;
   void onAdd(const AddEvent& e) override;

private:
   struct Average
   {
      RingBuffer<bool, 4800> buffer;
      uint16_t sum = 4800;

      using List = Average[8];
   };

private:
   void setup();

private:
   Average::List averageList;
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
