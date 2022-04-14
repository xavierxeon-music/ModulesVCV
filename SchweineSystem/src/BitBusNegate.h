#ifndef BitBusNegateH
#define BitBusNegateH

#include <rack.hpp>
using namespace rack;

#include "BitBusCommon.h"

class BitBusNegate : public Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusNegate();
   ~BitBusNegate();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

   void onAdd(const AddEvent& e) override;
   json_t* dataToJson() override;
   void dataFromJson(json_t* rootJson) override;

private:
   dsp::BooleanTrigger gateTrigger[8];
   bool gates[8];
};

struct BitBusNegateWidget : ModuleWidget
{
   BitBusNegateWidget(BitBusNegate* module);
};

#endif // NOT BitBusNegateH
