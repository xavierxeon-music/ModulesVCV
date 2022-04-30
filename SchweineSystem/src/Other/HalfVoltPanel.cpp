#include "HalfVolt.h"
#include "HalfVoltPanel.h"

#include <SchweineSystemMaster.h>

void HalfVolt::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

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

void HalfVoltWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/HalfVolt.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeInput(this, Vec(21.03, 327.87),  HalfVolt::Panel::Row8_In);
   makeInput(this, Vec(21.03, 290.57),  HalfVolt::Panel::Row7_In);
   makeInput(this, Vec(21.03, 253.28),  HalfVolt::Panel::Row6_In);
   makeInput(this, Vec(21.03, 215.99),  HalfVolt::Panel::Row5_In);
   makeInput(this, Vec(21.03, 178.70),  HalfVolt::Panel::Row4_In);
   makeInput(this, Vec(21.03, 141.41),  HalfVolt::Panel::Row3_In);
   makeInput(this, Vec(21.03, 104.12),  HalfVolt::Panel::Row2_In);
   makeInput(this, Vec(21.03, 66.83),  HalfVolt::Panel::Row1_In);

   makeOutput(this, Vec(53.96, 327.90), HalfVolt::Panel::Row8_Out);
   makeOutput(this, Vec(53.96, 290.61), HalfVolt::Panel::Row7_Out);
   makeOutput(this, Vec(53.96, 253.32), HalfVolt::Panel::Row6_Out);
   makeOutput(this, Vec(53.96, 216.03), HalfVolt::Panel::Row5_Out);
   makeOutput(this, Vec(53.96, 178.74), HalfVolt::Panel::Row4_Out);
   makeOutput(this, Vec(53.96, 141.45), HalfVolt::Panel::Row3_Out);
   makeOutput(this, Vec(53.96, 104.16), HalfVolt::Panel::Row2_Out);
   makeOutput(this, Vec(53.96, 66.86), HalfVolt::Panel::Row1_Out);
}

