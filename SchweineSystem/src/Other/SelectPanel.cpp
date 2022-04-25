#include "Select.h"
#include "SelectPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void Select::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Reset_Button, "Reset_Button");
   configButton(Panel::Next_Button, "Next_Button");
   configButton(Panel::Max_Button, "Max_Button");
   configButton(Panel::Min_Button, "Min_Button");
   configButton(Panel::Total_Button, "Total_Button");

   configInput(Panel::Reset_Gate, "Reset_Gate");
   configInput(Panel::Next_Gate, "Next_Gate");

   configOutput(Panel::Output, "Output");

   configDisplay(Panel::Text_Current_Display, "Current_Display");
   configDisplay(Panel::Text_Max_Display, "Max_Display");
   configDisplay(Panel::Text_Min_Display, "Min_Display");
   configDisplay(Panel::Text_Total_Display, "Total_Display");
}

void SelectWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Select.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(20.59, 306.38), Select::Panel::Reset_Button);
   makeButton(this, Vec(20.59, 258.38), Select::Panel::Next_Button);
   makeButton(this, Vec(20.37, 155.46), Select::Panel::Max_Button);
   makeButton(this, Vec(20.37, 112.62), Select::Panel::Min_Button);
   makeButton(this, Vec(20.37, 58.68), Select::Panel::Total_Button);

   makeInput(this, Vec(50.40, 306.38),  Select::Panel::Reset_Gate);
   makeInput(this, Vec(50.40, 258.38),  Select::Panel::Next_Gate);

   makeOutput(this, Vec(50.83, 355.83), Select::Panel::Output);

   makeDisplay(this, Vec(20.50, 201.48), 2, Select::Panel::Text_Current_Display, Select::Panel::RGB_Current_Display);
   makeDisplay(this, Vec(30.80, 143.46), 2, Select::Panel::Text_Max_Display, Select::Panel::RGB_Max_Display);
   makeDisplay(this, Vec(30.80, 100.62), 2, Select::Panel::Text_Min_Display, Select::Panel::RGB_Min_Display);
   makeDisplay(this, Vec(30.80, 46.68), 2, Select::Panel::Text_Total_Display, Select::Panel::RGB_Total_Display);
}

