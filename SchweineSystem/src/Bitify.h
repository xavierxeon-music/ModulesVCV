#ifndef BitifyH
#define BitifyH

#include <rack.hpp>
using namespace rack;

#include "Schweinesystem.h"

#include <Tools/BoolField.h>
#include <Tools/Range.h>

class Bitify : public Module
{
public:
   struct Panel;

public:
   Bitify();
   ~Bitify();

public:
   void process(const ProcessArgs& args) override;

private:
   void setup();
   void onExpanderChange(const ExpanderChangeEvent& e) override;

private:
   dsp::BooleanTrigger gateTriggers[8];
   bool gates[8] = {};

   BoolField8 boolFieldIn; // freeze content on hold
   BoolField8 boolFieldOutLast;
   Range::Mapper inputMapper;
   Range::Mapper outputMapper;
};

struct BitifyWidget : ModuleWidget
{
   BitifyWidget(Bitify* module);
};

#endif // BitifyH
