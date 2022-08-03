#ifndef MidiReplayPanelH
#define MidiReplayPanelH

#include "MidiReplay.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemDisplayOLED.h>

struct MidiReplay::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      PARAMS_LEN = 0
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
      INPUTS_LEN = 2
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
      // ledbuttons
      // lcds
      LIGHTS_LEN = 0
   };

};

#endif // NOT MidiReplayPanelH
