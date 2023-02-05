#include "NerdSeq.h"

NerdSeq::NerdSeq()
   : Svin::Module()
{
   setup();
}

void NerdSeq::process(const ProcessArgs& args)
{
}


// widget

NerdSeqWidget::NerdSeqWidget(NerdSeq* module)
: Svin::ModuleWidget(module)
{
   setup();
}

// create module
Model* modelNerdSeq = Svin::Origin::the()->addModule<NerdSeq, NerdSeqWidget>("NerdSeq");

