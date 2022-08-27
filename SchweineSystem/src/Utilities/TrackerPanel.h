#ifndef TrackerPanelH
#define TrackerPanelH

#include "Tracker.h"

#include <SvinCommon.h>
#include <SvinButton.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct Tracker::Panel
{
   enum ParamId
   {
      // buttons
      Display = 0,
      ModeManual = 1,
      // switches
      // ledbuttons
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
      Upload = 0,
      Reset = 1,
      Clock = 2,
      Group2_Pass = 3,
      Group1_Pass = 4,
      INPUTS_LEN = 5
   };

   enum OutputId
   {
      Group2_Output = 0,
      Group1_Output = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // lcds
      LIGHTS_LEN = 0
   };

};

#endif // NOT TrackerPanelH
