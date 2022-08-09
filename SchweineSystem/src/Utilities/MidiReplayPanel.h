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
      Display = 0,
      // switches
      // ledbuttons
      Loop = 1,
      // knobs
      PARAMS_LEN = 2
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
      Velocity = 0,
      Gate = 1,
      Pitch = 2,
      End = 3,
      OUTPUTS_LEN = 4
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