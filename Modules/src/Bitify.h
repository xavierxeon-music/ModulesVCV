#ifndef BitifyH
#define BitifyH

#include <rack.hpp>
using namespace rack;

#include "Schweinesystem.h"

class Bitify : public Module
{
public:
   struct Data;

public:
   Bitify();
   ~Bitify();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();

private:
   dsp::BooleanTrigger gateTriggers[8];
   bool gates[8] = {};
};

struct BitifyWidget : ModuleWidget
{
   BitifyWidget(Bitify* module);
};

#endif // BitifyH
