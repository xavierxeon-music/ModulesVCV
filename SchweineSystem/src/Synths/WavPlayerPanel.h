#ifndef WavPlayerPanelH
#define WavPlayerPanelH

#include "WavPlayer.h"

#include <SvinCommon.h>
#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

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

#endif // NOT WavPlayerPanelH
