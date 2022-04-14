#ifndef BitBusCVInH
#define BitBusCVInH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

#include <Tools/Range.h>

class BitBusCVIn : public Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusCVIn();
   ~BitBusCVIn();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void onAdd(const AddEvent& e) override;

private:
   Range::Mapper inputMapper;
};

struct BitBusCVInWidget : ModuleWidget
{
   BitBusCVInWidget(BitBusCVIn* module);
};

#endif // BitBusCVInH
