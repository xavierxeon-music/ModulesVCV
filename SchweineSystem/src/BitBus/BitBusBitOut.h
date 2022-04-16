#ifndef BitBusBitOutH
#define BitBusBitOutH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

class BitBusBitOut : public Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusBitOut();
   ~BitBusBitOut();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void onAdd(const AddEvent& e) override;
};

struct BitBusBitOutWidget : ModuleWidget
{
   BitBusBitOutWidget(BitBusBitOut* module);
};

#endif // BitBusBitOutH
