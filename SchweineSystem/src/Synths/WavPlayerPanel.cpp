#include "WavPlayer.h"
#include "WavPlayerPanel.h"

#include <SvinOrigin.h>

void WavPlayer::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::ManualReset, "ManualReset");

   configButton(Panel::Loop, "Loop");
   configButton(Panel::Play, "Play");

   configInput(Panel::Pitch, "Pitch");
   configInput(Panel::LoopOverride, "LoopOverride");
   configInput(Panel::Reset, "Reset");
   configInput(Panel::PlayOverride, "PlayOverride");

   configOutput(Panel::Right, "Right");
   configOutput(Panel::Left, "Left");
}

void WavPlayerWidget::setup()
{
   std::string panelPath = asset::plugin(Svin::Origin::the()->instance(), "res/Synths/WavPlayer.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(85.16, 171.53), WavPlayer::Panel::ManualReset);

   makeLEDButton(this, Vec(85.10, 207.15), WavPlayer::Panel::Loop, WavPlayer::Panel::RGB_Loop);
   makeLEDButton(this, Vec(85.10, 135.91), WavPlayer::Panel::Play, WavPlayer::Panel::RGB_Play);

   makeInput(this, Vec(55.54, 266.05),  WavPlayer::Panel::Pitch, false);
   makeInput(this, Vec(55.48, 207.15),  WavPlayer::Panel::LoopOverride, false);
   makeInput(this, Vec(55.54, 171.53),  WavPlayer::Panel::Reset, false);
   makeInput(this, Vec(55.48, 135.91),  WavPlayer::Panel::PlayOverride, false);

   makeOutput(this, Vec(55.48, 355.83), WavPlayer::Panel::Right, false);
   makeOutput(this, Vec(55.48, 318.15), WavPlayer::Panel::Left, true);

   makeOLED(this, Vec(10.00, 34.24), WavPlayer::Panel::Pixels_Display, 83, 60);
}

