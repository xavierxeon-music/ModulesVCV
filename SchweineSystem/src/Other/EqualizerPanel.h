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
      Knob_Smooth_Value = 1,
      Knob_Amount_Value = 2,
      Knob_Frequency_Value = 3,
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
      Amount = 2,
      Smooth = 3,
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
