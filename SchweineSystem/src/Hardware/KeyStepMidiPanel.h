#ifndef KeyStepMidiPanelH
#define KeyStepMidiPanelH

#include "KeyStepMidi.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemButtonLED.h>

struct KeyStepMidi::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Connect = 0,
      // knobs
      PARAMS_LEN = 1
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
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Connect = 0,
      // lcds
      LIGHTS_LEN = 3
   };

};

#endif // NOT KeyStepMidiPanelH
