#include "AturiaStepPanel.h"
#include "AturiaStep.h"

#include <SvinMaster.h>
#include <limits>

void AturiaStep::setup()
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

   configButton(Panel::Connect, "Connect");
   configButton(Panel::Drums, "Drums");

   configInput(Panel::Channel4_Select, "Channel4_Select");
   configInput(Panel::Channel3_Select, "Channel3_Select");
   configInput(Panel::Channel2_Select, "Channel2_Select");
   configInput(Panel::Channel1_Select, "Channel1_Select");

   configText(Panel::Text_Channel4_Pattern, "Channel4_Pattern");
   configText(Panel::Text_Channel3_Pattern, "Channel3_Pattern");
   configText(Panel::Text_Channel2_Pattern, "Channel2_Pattern");
   configText(Panel::Text_Channel1_Pattern, "Channel1_Pattern");
}

void AturiaStepWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Master::the()->instance(), "res/Hardware/AturiaStep.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(78.00, 261.39), AturiaStep::Panel::Channel4_Up);
   makeButton(this, Vec(78.00, 305.90), AturiaStep::Panel::Channel4_Down);
   makeButton(this, Vec(78.65, 192.18), AturiaStep::Panel::Channel3_Up);
   makeButton(this, Vec(78.65, 236.69), AturiaStep::Panel::Channel3_Down);
   makeButton(this, Vec(78.00, 122.98), AturiaStep::Panel::Channel2_Up);
   makeButton(this, Vec(78.00, 167.49), AturiaStep::Panel::Channel2_Down);
   makeButton(this, Vec(78.00, 53.77), AturiaStep::Panel::Channel1_Up);
   makeButton(this, Vec(78.00, 98.28), AturiaStep::Panel::Channel1_Down);

   makeLEDButton(this, Vec(50.98, 349.24), AturiaStep::Panel::Connect, AturiaStep::Panel::RGB_Connect);
   makeLEDButton(this, Vec(45.01, 42.78), AturiaStep::Panel::Drums, AturiaStep::Panel::RGB_Drums);

   makeInput(this, Vec(42.38, 283.65), AturiaStep::Panel::Channel4_Select);
   makeInput(this, Vec(43.04, 214.44), AturiaStep::Panel::Channel3_Select);
   makeInput(this, Vec(42.38, 145.23), AturiaStep::Panel::Channel2_Select);
   makeInput(this, Vec(42.38, 76.03), AturiaStep::Panel::Channel1_Select);

   makeLCD(this, Vec(61.00, 271.65), 2, AturiaStep::Panel::Text_Channel4_Pattern, AturiaStep::Panel::RGB_Channel4_Pattern);
   makeLCD(this, Vec(61.65, 202.44), 2, AturiaStep::Panel::Text_Channel3_Pattern, AturiaStep::Panel::RGB_Channel3_Pattern);
   makeLCD(this, Vec(61.00, 133.23), 2, AturiaStep::Panel::Text_Channel2_Pattern, AturiaStep::Panel::RGB_Channel2_Pattern);
   makeLCD(this, Vec(61.00, 64.03), 2, AturiaStep::Panel::Text_Channel1_Pattern, AturiaStep::Panel::RGB_Channel1_Pattern);
}