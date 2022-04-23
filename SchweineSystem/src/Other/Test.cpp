#include "Test.h"
#include "TestPanel.h"

#include <SchweineSystemMaster.h>

Test::Test()
   : Module()
   , panel(nullptr)
   , meter(this, Panel::Value_Channel1_Strip)
{
   panel = new Panel();
   setup();

   meter.setMaxValue(10);
}

Test::~Test()
{
   delete panel;
}

void Test::process(const ProcessArgs& args)
{
   const float value = inputs[Panel::Channel1_Input].getVoltage();
   meter.setValue(value);
}

TestWidget::TestWidget(Test* module)
: ModuleWidget()
{
   SvgPanel* mainPanel = setup(module);
   (void)mainPanel;
}

Model* modelTest = SchweineSystem::Master::the()->addModule<Test, TestWidget>("Test");
