#ifndef BitBusCVOutH
#define BitBusCVOutH

#include <rack.hpp>
using namespace rack;
#include "BitBusCommon.h"

#include <Tools/Range.h>

class BitBusCVOut : public Module, public BitBusCommon
{
public:
   struct Panel;

public:
   BitBusCVOut();
   ~BitBusCVOut();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void onAdd(const AddEvent& e) override;

private:
   Range::Mapper outputMapper;
};

struct BitBusCVOutWidget : ModuleWidget
{
   BitBusCVOutWidget(BitBusCVOut* module);
};

#endif // BitBusCVOutH
