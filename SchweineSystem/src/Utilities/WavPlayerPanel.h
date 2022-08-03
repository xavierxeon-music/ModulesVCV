#ifndef WavPlayerPanelH
#define WavPlayerPanelH

#include "WavPlayer.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemButton.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemDisplayOLED.h>
#include <SchweineSystemSwitch.h>

struct WavPlayer::Panel
{
   enum ParamId
   {
      // buttons
      ManualReset = 0,
      // switches
      LoopMode = 1,
      PlayMode = 2,
      // ledbuttons
      Loop = 3,
      Play = 4,
      // knobs
      PARAMS_LEN = 5
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
      // lcds
      LIGHTS_LEN = 6
   };

};

#endif // NOT WavPlayerPanelH
