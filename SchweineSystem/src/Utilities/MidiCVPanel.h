#ifndef MidiCVPanelH
#define MidiCVPanelH

#include "MidiCV.h"

#include <SchweineSystemCommon.h>

struct MidiCV::Panel
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
      DISPLAYS_LEN = 0
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      INPUTS_LEN = 0
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

#endif // NOT MidiCVPanelH
