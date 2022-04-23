#include "Test.h"
#include "TestPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

Test::Panel::Panel()
{
};


void Test::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configParam(Panel::Value_Channel1_Display, 0.f, 10, 0.f, "");

   configButton(Panel::Channel1_Up, "Channel1_Up");

   configInput(Panel::Channel1_Input, "Channel1_Input");

   configOutput(Panel::Channel1_Output, "Channel1_Output");
}

SvgPanel* TestWidget::setup(Test* module)
{
   setModule(module);
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Test.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(28.17, 183.73), Test::Panel::Channel1_Up, Test::Panel::Red_Channel1_Up);

   makeInput(this, Vec(28.16, 116.04),  Test::Panel::Channel1_Input);

   makeOutput(this, Vec(28.18, 79.12), Test::Panel::Channel1_Output);

   makeLight(this, Vec(28.93, 219.76), Test::Panel::Red_Channel1_Division);

   makeMeter(this, Vec(14.01, 235.39), 5, Test::Panel::Value_Channel1_Strip);

   makeDisplay(this, Vec(19.17, 146.21), 1, Test::Panel::Value_Channel1_Display, Test::Panel::Red_Channel1_Display);

   return mainPanel;
}

