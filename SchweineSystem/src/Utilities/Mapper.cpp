#include "Mapper.h"

Mapper::Mapper()
   : Svin::Module()
{
   setup();
}

void Mapper::process(const ProcessArgs& args)
{
}


// widget

MapperWidget::MapperWidget(Mapper* module)
: Svin::ModuleWidget(module)
{
   setup();
}

