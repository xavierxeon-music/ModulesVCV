#ifndef MidiReplayPanelH
#define MidiReplayPanelH

#include "MidiReplay.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemButton.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemDisplayOLED.h>

struct MidiReplay::Panel
{
   enum ParamId
   {
      // buttons
      Edit_Right = 0,
      Edit_Left = 1,
      Edit_Down = 2,
      Edit_Up = 3,
      Page = 4,
      // switches
      // ledbuttons
      Loop = 5,
      // knobs
      PARAMS_LEN = 6
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
      Clock = 1,
      Play = 2,
      INPUTS_LEN = 3
   };

   enum OutputId
   {
      End = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Loop = 0,
      // lcds
      LIGHTS_LEN = 3
   };

};

#endif // NOT MidiReplayPanelH
