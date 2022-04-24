#include "Test.h"
#include "TestPanel.h"

#include <SchweineSystemMaster.h>

Test::Test()
   : SchweineSystem::Module()
{
   setup();
}

void Test::process(const ProcessArgs& args)
{
}

TestWidget::TestWidget(Test* module)
: SchweineSystem::ModuleWidget(module)
{
   setup();
}

Model* modelTest = SchweineSystem::Master::the()->addModule<Test, TestWidget>("Test");
