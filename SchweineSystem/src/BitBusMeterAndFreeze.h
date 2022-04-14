#ifndef BitBusMeterAndFreezeH
#define BitBusMeterAndFreezeH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

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
   void setup();
};

struct BitBusMeterAndFreezeWidget : ModuleWidget
{
   BitBusMeterAndFreezeWidget(BitBusMeterAndFreeze* module);
};

#endif // NOT BitBusMeterAndFreezeH
