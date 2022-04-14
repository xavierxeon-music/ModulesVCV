#ifndef BitBusBitOutH
#define BitBusBitOutH

#include <rack.hpp>
using namespace rack;

class BitBusBitOut : public Module
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
};

struct BitBusBitOutWidget : ModuleWidget
{
   BitBusBitOutWidget(BitBusBitOut* module);
};

#endif // BitBusBitOutH
