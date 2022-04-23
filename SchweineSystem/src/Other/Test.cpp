#include "Test.h"
#include "TestPanel.h"

#include <SchweineSystemMaster.h>

Test::Test()
   : Module()
   , panel(nullptr)
{
   panel = new Panel();
   setup();
}

Test::~Test()
{
   delete panel;
}

void Test::process(const ProcessArgs& args)
{
}

TestWidget::TestWidget(Test* module)
: ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;
}

Model* modelTest = SchweineSystem::Master::the()->addModule<Test, TestWidget>("Test");
