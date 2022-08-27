#ifndef TrackerPanelH
#define TrackerPanelH

#include "Tracker.h"

#include <SvinCommon.h>
#include <SvinButton.h>
#include <SvinLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct Tracker::Panel
{
   enum ParamId
   {
      // buttons
      ModeManual = 0,
      Display = 1,
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
      ModeCV = 1,
      Reset = 2,
      Clock = 3,
      Channel2_Pass = 4,
      Channel1_Pass = 5,
      INPUTS_LEN = 6
   };

   enum OutputId
   {
      Channel2_Output = 0,
      Channel1_Output = 1,
      OUTPUTS_LEN = 2
   };

   enum LightId
   {
      // leds
      RGB_Internal_Status = 0,
      RGB_Remote_Status = 3,
      RGB_Input_Status = 6,
      // ledbuttons
      // lcds
      LIGHTS_LEN = 9
   };

};

#endif // NOT TrackerPanelH
