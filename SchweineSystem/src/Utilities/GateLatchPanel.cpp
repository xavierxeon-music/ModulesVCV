#include "GateLatch.h"
#include "GateLatchPanel.h"

#include <SchweineSystemMaster.h>

void GateLatch::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Reset_Button, "Reset_Button");

   configInput(Panel::Reset_Input, "Reset_Input");
   configInput(Panel::Row8_In, "Row8_In");
   configInput(Panel::Row7_In, "Row7_In");
   configInput(Panel::Row6_In, "Row6_In");
   configInput(Panel::Row5_In, "Row5_In");
   configInput(Panel::Row4_In, "Row4_In");
   configInput(Panel::Row3_In, "Row3_In");
   configInput(Panel::Row2_In, "Row2_In");
   configInput(Panel::Row1_In, "Row1_In");

   configOutput(Panel::Row8_Out, "Row8_Out");
   configOutput(Panel::Row7_Out, "Row7_Out");
   configOutput(Panel::Row6_Out, "Row6_Out");
   configOutput(Panel::Row5_Out, "Row5_Out");
   configOutput(Panel::Row4_Out, "Row4_Out");
   configOutput(Panel::Row3_Out, "Row3_Out");
   configOutput(Panel::Row2_Out, "Row2_Out");
   configOutput(Panel::Row1_Out, "Row1_Out");
}

void GateLatchWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/GateLatch.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(65.84, 355.83), GateLatch::Panel::Reset_Button);

   makeInput(this, Vec(24.00, 355.83),  GateLatch::Panel::Reset_Input);
   makeInput(this, Vec(24.17, 311.85),  GateLatch::Panel::Row8_In);
   makeInput(this, Vec(24.17, 276.41),  GateLatch::Panel::Row7_In);
   makeInput(this, Vec(24.17, 240.98),  GateLatch::Panel::Row6_In);
   makeInput(this, Vec(24.17, 205.55),  GateLatch::Panel::Row5_In);
   makeInput(this, Vec(24.17, 170.11),  GateLatch::Panel::Row4_In);
   makeInput(this, Vec(24.17, 134.68),  GateLatch::Panel::Row3_In);
   makeInput(this, Vec(24.17, 99.24),  GateLatch::Panel::Row2_In);
   makeInput(this, Vec(24.17, 63.81),  GateLatch::Panel::Row1_In);

   makeOutput(this, Vec(65.83, 311.85), GateLatch::Panel::Row8_Out);
   makeOutput(this, Vec(65.83, 276.41), GateLatch::Panel::Row7_Out);
   makeOutput(this, Vec(65.83, 240.98), GateLatch::Panel::Row6_Out);
   makeOutput(this, Vec(65.83, 205.55), GateLatch::Panel::Row5_Out);
   makeOutput(this, Vec(65.83, 170.11), GateLatch::Panel::Row4_Out);
   makeOutput(this, Vec(65.83, 134.68), GateLatch::Panel::Row3_Out);
   makeOutput(this, Vec(65.83, 99.24), GateLatch::Panel::Row2_Out);
   makeOutput(this, Vec(65.83, 63.81), GateLatch::Panel::Row1_Out);

   makeLED(this, Vec(45.00, 311.85), GateLatch::Panel::RGB_Row8_Status);
   makeLED(this, Vec(45.00, 276.41), GateLatch::Panel::RGB_Row7_Status);
   makeLED(this, Vec(45.00, 240.98), GateLatch::Panel::RGB_Row6_Status);
   makeLED(this, Vec(45.00, 205.55), GateLatch::Panel::RGB_Row5_Status);
   makeLED(this, Vec(45.00, 170.11), GateLatch::Panel::RGB_Row4_Status);
   makeLED(this, Vec(45.00, 134.68), GateLatch::Panel::RGB_Row3_Status);
   makeLED(this, Vec(45.00, 99.24), GateLatch::Panel::RGB_Row2_Status);
   makeLED(this, Vec(45.00, 63.81), GateLatch::Panel::RGB_Row1_Status);
}

