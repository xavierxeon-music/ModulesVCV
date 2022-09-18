#ifndef AturiaStepHPP
#define AturiaStepHPP

#include "AturiaStep.h"

#include <SvinOrigin.h>

struct AturiaStep::Panel
{
   enum ParamId
   {
      // buttons
      Channel4_Up = 0,
      Channel4_Down = 1,
      Channel3_Up = 2,
      Channel3_Down = 3,
      Channel2_Up = 4,
      Channel2_Down = 5,
      Channel1_Up = 6,
      Channel1_Down = 7,
      // switches
      // ledbuttons
      Connect = 8,
      Drums = 9,
      // knobs
      // sliders
      PARAMS_LEN = 10
   };

   enum DisplayId
   {
      // lcd
      Text_Channel4_Pattern = 0,
      Text_Channel3_Pattern = 1,
      Text_Channel2_Pattern = 2,
      Text_Channel1_Pattern = 3,
      // oled
      DISPLAYS_LEN = 4
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Channel4_Select = 0,
      Channel3_Select = 1,
      Channel2_Select = 2,
      Channel1_Select = 3,
      INPUTS_LEN = 4
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Connect = 0,
      RGB_Drums = 3,
      // sliders
      LIGHTS_LEN = 6
   };

};

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
}

void AturiaStepWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Hardware/AturiaStep.svg");
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

   makeInput(this, Vec(42.38, 283.65),  AturiaStep::Panel::Channel4_Select, false);
   makeInput(this, Vec(43.04, 214.44),  AturiaStep::Panel::Channel3_Select, false);
   makeInput(this, Vec(42.38, 145.23),  AturiaStep::Panel::Channel2_Select, false);
   makeInput(this, Vec(42.38, 76.03),  AturiaStep::Panel::Channel1_Select, false);

   makeLCD(this, Vec(61.00, 271.65), 2, AturiaStep::Panel::Text_Channel4_Pattern, 18);
   makeLCD(this, Vec(61.65, 202.44), 2, AturiaStep::Panel::Text_Channel3_Pattern, 18);
   makeLCD(this, Vec(61.00, 133.23), 2, AturiaStep::Panel::Text_Channel2_Pattern, 18);
   makeLCD(this, Vec(61.00, 64.03), 2, AturiaStep::Panel::Text_Channel1_Pattern, 18);
}

Model* modelAturiaStep = Svin::Origin::the()->addModule<AturiaStep, AturiaStepWidget>("AturiaStep");

#endif // NOT AturiaStepHPP
