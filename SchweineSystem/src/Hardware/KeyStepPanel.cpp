#include "KeyStep.h"
#include "KeyStepPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void KeyStep::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::Channel4_Up, "Channel4_Up");
   configButton(Panel::Channel4_Down, "Channel4_Down");
   configButton(Panel::Channel3_Up, "Channel3_Up");
   configButton(Panel::Channel3_Down, "Channel3_Down");
   configButton(Panel::Channel2_Up, "Channel2_Up");
   configButton(Panel::Channel2_Down, "Channel2_Down");
   configButton(Panel::Channel1_Up, "Channel1_Up");
   configButton(Panel::Channel1_Down, "Channel1_Down");

   configSwitch(Panel::Channel1_Drums, 0.0f, 1.0f, 0.0f, "Channel1_Drums");

   configButton(Panel::Connect, "Connect");

   configInput(Panel::Channel4_Select, "Channel4_Select");
   configInput(Panel::Channel3_Select, "Channel3_Select");
   configInput(Panel::Channel2_Select, "Channel2_Select");
   configInput(Panel::Channel1_Select, "Channel1_Select");

   configText(Panel::Text_Channel4_Pattern, "Channel4_Pattern");
   configText(Panel::Text_Channel3_Pattern, "Channel3_Pattern");
   configText(Panel::Text_Channel2_Pattern, "Channel2_Pattern");
   configText(Panel::Text_Channel1_Pattern, "Channel1_Pattern");
}

void KeyStepWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/KeyStep.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(73.98, 319.74), KeyStep::Panel::Channel4_Up);
   makeButton(this, Vec(16.02, 319.74), KeyStep::Panel::Channel4_Down);
   makeButton(this, Vec(73.98, 243.32), KeyStep::Panel::Channel3_Up);
   makeButton(this, Vec(16.02, 243.32), KeyStep::Panel::Channel3_Down);
   makeButton(this, Vec(73.98, 166.91), KeyStep::Panel::Channel2_Up);
   makeButton(this, Vec(16.02, 166.91), KeyStep::Panel::Channel2_Down);
   makeButton(this, Vec(73.98, 90.49), KeyStep::Panel::Channel1_Up);
   makeButton(this, Vec(16.02, 90.49), KeyStep::Panel::Channel1_Down);

   makeSwitch(this, Vec(69.74, 60.72), KeyStep::Panel::Channel1_Drums);

   makeLEDButton(this, Vec(59.84, 355.43), KeyStep::Panel::Connect, KeyStep::Panel::RGB_Connect);

   makeInput(this, Vec(46.29, 289.69),  KeyStep::Panel::Channel4_Select);
   makeInput(this, Vec(46.29, 213.27),  KeyStep::Panel::Channel3_Select);
   makeInput(this, Vec(46.29, 136.85),  KeyStep::Panel::Channel2_Select);
   makeInput(this, Vec(46.29, 60.43),  KeyStep::Panel::Channel1_Select);

   makeLCD(this, Vec(29.29, 307.74), 2, KeyStep::Panel::Text_Channel4_Pattern, KeyStep::Panel::RGB_Channel4_Pattern);
   makeLCD(this, Vec(29.29, 231.32), 2, KeyStep::Panel::Text_Channel3_Pattern, KeyStep::Panel::RGB_Channel3_Pattern);
   makeLCD(this, Vec(29.29, 154.91), 2, KeyStep::Panel::Text_Channel2_Pattern, KeyStep::Panel::RGB_Channel2_Pattern);
   makeLCD(this, Vec(29.29, 78.49), 2, KeyStep::Panel::Text_Channel1_Pattern, KeyStep::Panel::RGB_Channel1_Pattern);
}

