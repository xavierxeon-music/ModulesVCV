#ifndef WavPlayerHPP
#define WavPlayerHPP

#include "WavPlayer.h"

#include <SvinOrigin.h>

struct WavPlayer::Panel
{
   enum ParamId
   {
      // buttons
      ManualReset = 0,
      // switches
      // ledbuttons
      Loop = 1,
      Play = 2,
      // knobs
      // sliders
      PARAMS_LEN = 3
   };

   enum DisplayId
   {
      // lcd
      // oled
      Pixels_Display = 0,
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Pitch = 0,
      LoopOverride = 1,
      Reset = 2,
      PlayOverride = 3,
      INPUTS_LEN = 4
   };

   enum OutputId
   {
      Right = 0,
      Left = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Loop = 0,
      RGB_Play = 3,
      // sliders
      LIGHTS_LEN = 6
   };

};

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
   makePanel("res/Synths/WavPlayer.svg");

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

#endif // NOT WavPlayerHPP
