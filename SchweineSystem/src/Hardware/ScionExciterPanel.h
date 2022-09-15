#ifndef ScionExciterPanelH
#define ScionExciterPanelH

#include "ScionExciter.h"

#include <SvinCommon.h>
#include <SvinKnob.h>
#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct ScionExciter::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      Master_Amplitude_Attenuate = 0,
      Master_Amplitude_LFO = 1,
      Master_Smooth_Attenuate = 2,
      Master_Smooth_LFO = 3,
      Noise_Amplitude1_Attenuate = 4,
      Noise_Amplitude1_LFO = 5,
      Noise_Smooth1_Attenuate = 6,
      Noise_Smooth1_LFO = 7,
      Base1_Amplitude2_Attenuate = 8,
      Base1_Amplitude2_LFO = 9,
      Base1_Pitch_Attenuate = 10,
      Base1_Pitch_LFO = 11,
      // sliders
      Master_Amplitude_Value = 12,
      Master_Smooth_Value = 13,
      Noise_Amplitude1_Value = 14,
      Noise_Smooth1_Value = 15,
      Base1_Amplitude2_Value = 16,
      Base1_Pitch_Value = 17,
      PARAMS_LEN = 18
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
      Master_Amplitude_Modulate = 0,
      Master_Smooth_Modulate = 1,
      Noise_Amplitude1_Modulate = 2,
      Noise_Smooth1_Modulate = 3,
      Base1_Amplitude2_Modulate = 4,
      Base1_Pitch_Modulate = 5,
      INPUTS_LEN = 6
   };

   enum OutputId
   {
      Master_Base_Out = 0,
      Master_Exciter_Out = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // sliders
      RGB_Master_Amplitude_Value = 0,
      RGB_Master_Smooth_Value = 3,
      RGB_Noise_Amplitude1_Value = 6,
      RGB_Noise_Smooth1_Value = 9,
      RGB_Base1_Amplitude2_Value = 12,
      RGB_Base1_Pitch_Value = 15,
      LIGHTS_LEN = 18
   };

};

#endif // NOT ScionExciterPanelH
