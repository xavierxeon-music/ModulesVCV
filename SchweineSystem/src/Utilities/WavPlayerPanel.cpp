#include "WavPlayer.h"
#include "WavPlayerPanel.h"

#include <SchweineSystemMaster.h>
#include <SchweineSystemSwitch.h>

void WavPlayer::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::ManualReset, "ManualReset");

   configSwitch(Panel::LoopMode, 0.0f, 1.0f, 0.0f, "LoopMode");
   configSwitch(Panel::PlayMode, 0.0f, 1.0f, 0.0f, "PlayMode");

   configButton(Panel::Loop, "Loop");
   configButton(Panel::Play, "Play");

   configInput(Panel::Pitch, "Pitch");
   configInput(Panel::LoopOverride, "LoopOverride");
   configInput(Panel::Reset, "Reset");
   configInput(Panel::PlayOverride, "PlayOverride");

   configOutput(Panel::Right, "Right");
   configOutput(Panel::Left, "Left");

   configPixels(Panel::Pixels_Display, 83, 60, "Display");
}

void WavPlayerWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/WavPlayer.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(85.16, 195.96), WavPlayer::Panel::ManualReset);

   makeSwitch(this, Vec(31.35, 232.58), WavPlayer::Panel::LoopMode);
   makeSwitch(this, Vec(31.35, 161.34), WavPlayer::Panel::PlayMode);

   makeLEDButton(this, Vec(85.10, 231.59), WavPlayer::Panel::Loop, WavPlayer::Panel::RGB_Loop);
   makeLEDButton(this, Vec(85.10, 160.34), WavPlayer::Panel::Play, WavPlayer::Panel::RGB_Play);

   makeInput(this, Vec(55.54, 275.05),  WavPlayer::Panel::Pitch);
   makeInput(this, Vec(55.48, 231.59),  WavPlayer::Panel::LoopOverride);
   makeInput(this, Vec(55.54, 195.96),  WavPlayer::Panel::Reset);
   makeInput(this, Vec(55.48, 160.34),  WavPlayer::Panel::PlayOverride);

   makeOutput(this, Vec(55.48, 355.83), WavPlayer::Panel::Right);
   makeOutput(this, Vec(55.48, 318.15), WavPlayer::Panel::Left);

   makeOLED(this, Vec(10.00, 34.24), WavPlayer::Panel::Pixels_Display, 83, 60);
}

