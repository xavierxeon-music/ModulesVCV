#ifndef MidiReplayPanelH
#define MidiReplayPanelH

#include "MidiReplay.h"

#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinCommon.h>
#include <SvinDisplayOLED.h>

struct MidiReplay::Panel
{
   enum ParamId
   {
      // buttons
      Page = 0,
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
