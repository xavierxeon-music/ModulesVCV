#ifndef WavPlayerPanelH
#define WavPlayerPanelH

#include "WavPlayer.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemDisplayLCD.h>
#include <SchweineSystemDisplayOLED.h>

struct WavPlayer::Panel
{
   enum ParamId
   {
      // buttons
      ManualReset = 0,
      // switches
      PlayMode = 1,
      LoopMode = 2,
      // ledbuttons
      Play = 3,
      Loop = 4,
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
      Reset = 0,
      PlayOverride = 1,
      LoopOverride = 2,
      INPUTS_LEN = 3
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
      RGB_Play = 0,
      RGB_Loop = 3,
      // lcds
      LIGHTS_LEN = 6
   };

};

#endif // NOT WavPlayerPanelH
