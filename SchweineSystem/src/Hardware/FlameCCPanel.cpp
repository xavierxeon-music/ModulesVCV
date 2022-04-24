#include "FlameCC.h"
#include "FlameCCPanel.h"

#include <SchweineSystemMaster.h>

void FlameCC::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configInput(Panel::Row8_InB, "Row8_InB");
   configInput(Panel::Row8_InA, "Row8_InA");
   configInput(Panel::Row7_InB, "Row7_InB");
   configInput(Panel::Row7_InA, "Row7_InA");
   configInput(Panel::Row6_InB, "Row6_InB");
   configInput(Panel::Row6_InA, "Row6_InA");
   configInput(Panel::Row5_InB, "Row5_InB");
   configInput(Panel::Row5_InA, "Row5_InA");
   configInput(Panel::Row4_InB, "Row4_InB");
   configInput(Panel::Row4_InA, "Row4_InA");
   configInput(Panel::Row3_InB, "Row3_InB");
   configInput(Panel::Row3_InA, "Row3_InA");
   configInput(Panel::Row2_InB, "Row2_InB");
   configInput(Panel::Row2_InA, "Row2_InA");
   configInput(Panel::Row1_InB, "Row1_InB");
   configInput(Panel::Row1_InA, "Row1_InA");
}

void FlameCCWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/FlameCC.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeLEDButton(this, Vec(57.77, 359.49), FlameCC::Panel::Connect, FlameCC::Panel::RGB_Connect);

   makeInput(this, Vec(63.83, 327.95),  FlameCC::Panel::Row8_InB);
   makeInput(this, Vec(26.17, 327.88),  FlameCC::Panel::Row8_InA);
   makeInput(this, Vec(63.83, 290.66),  FlameCC::Panel::Row7_InB);
   makeInput(this, Vec(26.17, 290.58),  FlameCC::Panel::Row7_InA);
   makeInput(this, Vec(63.83, 253.36),  FlameCC::Panel::Row6_InB);
   makeInput(this, Vec(26.17, 253.29),  FlameCC::Panel::Row6_InA);
   makeInput(this, Vec(63.83, 216.07),  FlameCC::Panel::Row5_InB);
   makeInput(this, Vec(26.17, 215.99),  FlameCC::Panel::Row5_InA);
   makeInput(this, Vec(63.83, 178.77),  FlameCC::Panel::Row4_InB);
   makeInput(this, Vec(26.17, 178.70),  FlameCC::Panel::Row4_InA);
   makeInput(this, Vec(63.83, 141.47),  FlameCC::Panel::Row3_InB);
   makeInput(this, Vec(26.17, 141.40),  FlameCC::Panel::Row3_InA);
   makeInput(this, Vec(63.83, 104.18),  FlameCC::Panel::Row2_InB);
   makeInput(this, Vec(26.17, 104.10),  FlameCC::Panel::Row2_InA);
   makeInput(this, Vec(63.83, 66.88),  FlameCC::Panel::Row1_InB);
   makeInput(this, Vec(26.17, 66.81),  FlameCC::Panel::Row1_InA);
}

