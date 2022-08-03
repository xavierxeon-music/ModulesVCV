#include "FlameCC.h"
#include "FlameCCPanel.h"

#include <SchweineSystemButtonLED.h>
#include <SchweineSystemMaster.h>

void FlameCC::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configSwitch(Panel::Row8_HalfB, 0.0f, 1.0f, 0.0f, "Row8_HalfB");
   configSwitch(Panel::Row8_HalfA, 0.0f, 1.0f, 0.0f, "Row8_HalfA");
   configSwitch(Panel::Row7_HalfB, 0.0f, 1.0f, 0.0f, "Row7_HalfB");
   configSwitch(Panel::Row7_HalfA, 0.0f, 1.0f, 0.0f, "Row7_HalfA");
   configSwitch(Panel::Row6_HalfB, 0.0f, 1.0f, 0.0f, "Row6_HalfB");
   configSwitch(Panel::Row6_HalfA, 0.0f, 1.0f, 0.0f, "Row6_HalfA");
   configSwitch(Panel::Row5_HalfB, 0.0f, 1.0f, 0.0f, "Row5_HalfB");
   configSwitch(Panel::Row5_HalfA, 0.0f, 1.0f, 0.0f, "Row5_HalfA");
   configSwitch(Panel::Row4_HalfB, 0.0f, 1.0f, 0.0f, "Row4_HalfB");
   configSwitch(Panel::Row4_HalfA, 0.0f, 1.0f, 0.0f, "Row4_HalfA");
   configSwitch(Panel::Row3_HalfB, 0.0f, 1.0f, 0.0f, "Row3_HalfB");
   configSwitch(Panel::Row3_HalfA, 0.0f, 1.0f, 0.0f, "Row3_HalfA");
   configSwitch(Panel::Row2_HalfB, 0.0f, 1.0f, 0.0f, "Row2_HalfB");
   configSwitch(Panel::Row2_HalfA, 0.0f, 1.0f, 0.0f, "Row2_HalfA");
   configSwitch(Panel::Row1_HalfB, 0.0f, 1.0f, 0.0f, "Row1_HalfB");
   configSwitch(Panel::Row1_HalfA, 0.0f, 1.0f, 0.0f, "Row1_HalfA");

   configButton(Panel::Connect, "Connect");

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
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Hardware/FlameCC.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeSwitch(this, Vec(114.04, 327.11), FlameCC::Panel::Row8_HalfB);
   makeSwitch(this, Vec(20.96, 327.18), FlameCC::Panel::Row8_HalfA);
   makeSwitch(this, Vec(114.04, 290.46), FlameCC::Panel::Row7_HalfB);
   makeSwitch(this, Vec(20.96, 290.54), FlameCC::Panel::Row7_HalfA);
   makeSwitch(this, Vec(114.04, 253.82), FlameCC::Panel::Row6_HalfB);
   makeSwitch(this, Vec(20.96, 253.90), FlameCC::Panel::Row6_HalfA);
   makeSwitch(this, Vec(114.04, 217.18), FlameCC::Panel::Row5_HalfB);
   makeSwitch(this, Vec(20.96, 217.25), FlameCC::Panel::Row5_HalfA);
   makeSwitch(this, Vec(114.04, 180.54), FlameCC::Panel::Row4_HalfB);
   makeSwitch(this, Vec(20.96, 180.61), FlameCC::Panel::Row4_HalfA);
   makeSwitch(this, Vec(114.04, 143.89), FlameCC::Panel::Row3_HalfB);
   makeSwitch(this, Vec(20.96, 143.97), FlameCC::Panel::Row3_HalfA);
   makeSwitch(this, Vec(114.04, 107.25), FlameCC::Panel::Row2_HalfB);
   makeSwitch(this, Vec(20.96, 107.32), FlameCC::Panel::Row2_HalfA);
   makeSwitch(this, Vec(114.04, 70.61), FlameCC::Panel::Row1_HalfB);
   makeSwitch(this, Vec(20.96, 70.68), FlameCC::Panel::Row1_HalfA);

   makeLEDButton(this, Vec(80.27, 360.35), FlameCC::Panel::Connect, FlameCC::Panel::RGB_Connect);

   makeInput(this, Vec(88.33, 327.18),  FlameCC::Panel::Row8_InB);
   makeInput(this, Vec(46.67, 327.18),  FlameCC::Panel::Row8_InA);
   makeInput(this, Vec(88.33, 290.54),  FlameCC::Panel::Row7_InB);
   makeInput(this, Vec(46.67, 290.54),  FlameCC::Panel::Row7_InA);
   makeInput(this, Vec(88.33, 253.89),  FlameCC::Panel::Row6_InB);
   makeInput(this, Vec(46.67, 253.89),  FlameCC::Panel::Row6_InA);
   makeInput(this, Vec(88.33, 217.25),  FlameCC::Panel::Row5_InB);
   makeInput(this, Vec(46.67, 217.25),  FlameCC::Panel::Row5_InA);
   makeInput(this, Vec(88.33, 180.61),  FlameCC::Panel::Row4_InB);
   makeInput(this, Vec(46.67, 180.61),  FlameCC::Panel::Row4_InA);
   makeInput(this, Vec(88.33, 143.97),  FlameCC::Panel::Row3_InB);
   makeInput(this, Vec(46.67, 143.97),  FlameCC::Panel::Row3_InA);
   makeInput(this, Vec(88.33, 107.32),  FlameCC::Panel::Row2_InB);
   makeInput(this, Vec(46.67, 107.32),  FlameCC::Panel::Row2_InA);
   makeInput(this, Vec(88.33, 70.68),  FlameCC::Panel::Row1_InB);
   makeInput(this, Vec(46.67, 70.68),  FlameCC::Panel::Row1_InA);
}

