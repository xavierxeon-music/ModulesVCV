#include "Select.h"
#include "SelectPanel.h"

#include <SchweineSystemMaster.h>

Select::Select()
   : SchweineSystem::Module()
{
   setup();
}

void Select::process(const ProcessArgs& args)
{
}

SelectWidget::SelectWidget(Select* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelSelect = SchweineSystem::Master::the()->addModule<Select, SelectWidget>("Select");
