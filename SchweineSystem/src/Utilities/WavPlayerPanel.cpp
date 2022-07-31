#include "WavPlayer.h"
#include "WavPlayerPanel.h"

#include <SchweineSystemMaster.h>

void WavPlayer::setup()
{
   config(Panel::PARAMS_LEN, Panel::INPUTS_LEN, Panel::OUTPUTS_LEN, Panel::LIGHTS_LEN);

   configButton(Panel::ManualReset, "ManualReset");

   configSwitch(Panel::PlayMode, 0.0f, 1.0f, 0.0f, "PlayMode");
   configSwitch(Panel::LoopMode, 0.0f, 1.0f, 0.0f, "LoopMode");

   configButton(Panel::Play, "Play");
   configButton(Panel::Loop, "Loop");

   configInput(Panel::Reset, "Reset");
   configInput(Panel::PlayOverride, "PlayOverride");
   configInput(Panel::LoopOverride, "LoopOverride");

   configOutput(Panel::Right, "Right");
   configOutput(Panel::Left, "Left");

   configPixels(Panel::Pixels_Display, 83, 90, "Display");
}

void WavPlayerWidget::setup()
{
   std::string panelPath = asset::plugin(SchweineSystem::Master::the()->instance(), "res/Utilities/WavPlayer.svg");
   SvgPanel* mainPanel = createPanel(panelPath);
   setPanel(mainPanel);

   makeButton(this, Vec(85.16, 262.59), WavPlayer::Panel::ManualReset);

   makeSwitch(this, Vec(31.35, 228.34), WavPlayer::Panel::PlayMode);
   makeSwitch(this, Vec(31.35, 193.09), WavPlayer::Panel::LoopMode);

   makeLEDButton(this, Vec(85.10, 227.34), WavPlayer::Panel::Play, WavPlayer::Panel::RGB_Play);
   makeLEDButton(this, Vec(85.10, 192.10), WavPlayer::Panel::Loop, WavPlayer::Panel::RGB_Loop);

   makeInput(this, Vec(55.54, 262.59),  WavPlayer::Panel::Reset);
   makeInput(this, Vec(55.48, 227.34),  WavPlayer::Panel::PlayOverride);
   makeInput(this, Vec(55.48, 192.10),  WavPlayer::Panel::LoopOverride);

   makeOutput(this, Vec(55.48, 355.83), WavPlayer::Panel::Right);
   makeOutput(this, Vec(55.48, 318.15), WavPlayer::Panel::Left);

   makeOLED(this, Vec(10.00, 39.24), WavPlayer::Panel::Pixels_Display, 83, 90);
}

