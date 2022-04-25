#ifndef EqualizerPanelH
#define EqualizerPanelH

#include "Equalizer.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>

struct Equalizer::Panel
{
   enum ParamId
   {
      // buttons
      // ledbuttons
      Frequency_Quantize = 0,
      // knobs
      Knob_Drive_Knob = 1,
      Knob_Resonance_Knob = 2,
      Knob_Frequency_Knob = 3,
      PARAMS_LEN = 4
   };

   enum DisplayId
   {
      Text_Frequency_Display = 0,
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      AudioInput = 0,
      Freqeuncy = 1,
      Resonance = 2,
      Drive = 3,
      INPUTS_LEN = 4
   };

   enum OutputId
   {
      AudioOutput = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // buttons
      RGB_Frequency_Quantize = 0,
      // displays
      RGB_Frequency_Display = 3,
      LIGHTS_LEN = 6
   };

};

#endif // NOT EqualizerPanelH
