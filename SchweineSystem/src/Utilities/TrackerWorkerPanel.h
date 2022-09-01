#ifndef TrackerWorkerPanelH
#define TrackerWorkerPanelH

#include "TrackerWorker.h"

#include <SvinCommon.h>
#include <SvinButton.h>
#include <SvinButtonLED.h>
#include <SvinDisplayOLED.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct TrackerWorker::Panel
{
   enum ParamId
   {
      // buttons
      Mode = 0,
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
      Upload = 0,
      Group2_Pass = 1,
      Group1_Pass = 2,
      INPUTS_LEN = 3
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
      RGB_Loop = 0,
      // lcds
      LIGHTS_LEN = 3
   };

};

#endif // NOT TrackerWorkerPanelH
