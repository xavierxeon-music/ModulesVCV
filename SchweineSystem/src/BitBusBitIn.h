#ifndef BitBusBitInH
#define BitBusBitInH

#include <rack.hpp>
using namespace rack;

class BitBusBitIn : public Module
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
};

struct BitBusBitInWidget : ModuleWidget
{
   BitBusBitInWidget(BitBusBitIn* module);
};

#endif // BitBusBitInH
