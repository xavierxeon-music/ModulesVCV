#ifndef BitBusBitInH
#define BitBusBitInH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

#include "SchweineSystemCommon.h"

class BitBusBitIn : public Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusBitIn();
   ~BitBusBitIn();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void onAdd(const AddEvent& e) override;

private:
   SchweineSystem::Input::List inputList;
};

struct BitBusBitInWidget : ModuleWidget
{
   BitBusBitInWidget(BitBusBitIn* module);
};

#endif // BitBusBitInH
