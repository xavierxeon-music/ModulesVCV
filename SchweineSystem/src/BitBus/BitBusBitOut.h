#ifndef BitBusBitOutH
#define BitBusBitOutH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

#include "SchweineSystemCommon.h"

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

private:
   SchweineSystem::Output::List outputList;
};

struct BitBusBitOutWidget : ModuleWidget
{
   BitBusBitOutWidget(BitBusBitOut* module);
};

#endif // BitBusBitOutH
