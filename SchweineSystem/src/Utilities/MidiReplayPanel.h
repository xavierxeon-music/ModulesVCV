#ifndef MidiReplayPanelH
#define MidiReplayPanelH

#include "MidiReplay.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemButton.h>
#include <SchweineSystemLED.h>
#include <SchweineSystemDisplayOLED.h>

struct MidiReplay::Panel
{
   enum ParamId
   {
      // buttons
      Display = 0,
      // switches
      // ledbuttons
      // knobs
      PARAMS_LEN = 1
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
      OUTPUTS_LEN = 3
   };

   enum LightId
   {
      // leds
      RGB_PlayStatus = 0,
      // ledbuttons
      // lcds
      LIGHTS_LEN = 3
   };

};

#endif // NOT MidiReplayPanelH
