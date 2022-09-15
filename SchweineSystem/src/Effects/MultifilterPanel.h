#ifndef MultifilterPanelH
#define MultifilterPanelH

#include "Multifilter.h"

#include <SvinCommon.h>
#include <SvinKnob.h>
#include <SvinButtonLED.h>
#include <SvinSlider.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct Multifilter::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Quantize = 0,
      // knobs
      Offset = 1,
      Drive = 2,
      Reso = 3,
      // sliders
      Mode = 4,
      PARAMS_LEN = 5
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
      In = 0,
      Pitch = 1,
      OffsetOverride = 2,
      DriveOverride = 3,
      ResoOverride = 4,
      INPUTS_LEN = 5
   };

   enum OutputId
   {
      Out = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      RGB_Quantize = 0,
      // sliders
      RGB_Mode = 3,
      LIGHTS_LEN = 6
   };

};

#endif // NOT MultifilterPanelH
