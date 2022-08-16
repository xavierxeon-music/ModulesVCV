#include "KeyStepChannel.h"
#include "KeyStepChannelPanel.h"

#include <SchweineSystemMaster.h>
#include <limits>

void KeyStepChannel::setup()
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

   configInput(Panel::Reset, "Reset");
   configInput(Panel::Channel4_Select, "Channel4_Select");
   configInput(Panel::Channel3_Select, "Channel3_Select");
   configInput(Panel::Channel2_Select, "Channel2_Select");
   configInput(Panel::Channel1_Select, "Channel1_Select");

   configText(Panel::Text_Channel4_Pattern, "Channel4_Pattern");
   configText(Panel::Text_Channel3_Pattern, "Channel3_Pattern");
   configText(Panel::Text_Channel2_Pattern, "Channel2_Pattern");
   configText(Panel::Text_Channel1_Pattern, "Channel1_Pattern");
}

void KeyStepChannelWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Hardware/KeyStepChannel.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(73.98, 303.74), KeyStepChannel::Panel::Channel4_Up);
   makeButton(this, Vec(16.02, 303.74), KeyStepChannel::Panel::Channel4_Down);
   makeButton(this, Vec(73.98, 232.32), KeyStepChannel::Panel::Channel3_Up);
   makeButton(this, Vec(16.02, 232.32), KeyStepChannel::Panel::Channel3_Down);
   makeButton(this, Vec(73.98, 160.91), KeyStepChannel::Panel::Channel2_Up);
   makeButton(this, Vec(16.02, 160.91), KeyStepChannel::Panel::Channel2_Down);
   makeButton(this, Vec(73.98, 89.49), KeyStepChannel::Panel::Channel1_Up);
   makeButton(this, Vec(16.02, 89.49), KeyStepChannel::Panel::Channel1_Down);

   makeSwitch(this, Vec(69.74, 59.72), KeyStepChannel::Panel::Channel1_Drums);

   makeLEDButton(this, Vec(65.29, 356.20), KeyStepChannel::Panel::Connect, KeyStepChannel::Panel::RGB_Connect);

   makeInput(this, Vec(24.17, 355.84),  KeyStepChannel::Panel::Reset);
   makeInput(this, Vec(46.29, 273.69),  KeyStepChannel::Panel::Channel4_Select);
   makeInput(this, Vec(46.29, 202.27),  KeyStepChannel::Panel::Channel3_Select);
   makeInput(this, Vec(46.29, 130.85),  KeyStepChannel::Panel::Channel2_Select);
   makeInput(this, Vec(46.29, 59.43),  KeyStepChannel::Panel::Channel1_Select);

   makeLCD(this, Vec(29.29, 291.74), 2, KeyStepChannel::Panel::Text_Channel4_Pattern, KeyStepChannel::Panel::RGB_Channel4_Pattern);
   makeLCD(this, Vec(29.29, 220.32), 2, KeyStepChannel::Panel::Text_Channel3_Pattern, KeyStepChannel::Panel::RGB_Channel3_Pattern);
   makeLCD(this, Vec(29.29, 148.91), 2, KeyStepChannel::Panel::Text_Channel2_Pattern, KeyStepChannel::Panel::RGB_Channel2_Pattern);
   makeLCD(this, Vec(29.29, 77.49), 2, KeyStepChannel::Panel::Text_Channel1_Pattern, KeyStepChannel::Panel::RGB_Channel1_Pattern);
}

