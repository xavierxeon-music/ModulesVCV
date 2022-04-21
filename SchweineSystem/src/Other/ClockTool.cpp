#include "ClockTool.h"
#include "ClockToolPanel.h"

#include "SchweineSystemMaster.h"

ClockTool::ClockTool()
   : Module()
{
   setup();
}

ClockTool::~ClockTool()
{
}

void ClockTool::process(const ProcessArgs& args)
{
}

ClockToolWidget::ClockToolWidget(ClockTool* module)
: ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;
}

Model* modelClockTool = SchweineSystem::Master::the()->addModule<ClockTool, ClockToolWidget>("ClockTool");

