#ifndef SelectPanelH
#define SelectPanelH

#include "Select.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLCDDisplay.h>

struct Select::Panel
{
   enum ParamId
   {
      // buttons
      Reset_Button = 0,
      Next_Button = 1,
      Max_Button = 2,
      Min_Button = 3,
      Total_Button = 4,
      // ledbuttons
      // knobs
      PARAMS_LEN = 5
   };

   enum DisplayId
   {
      Text_Current_Display = 0,
      Text_Max_Display = 1,
      Text_Min_Display = 2,
      Text_Total_Display = 3,
      DISPLAYS_LEN = 4
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      Reset_Gate = 0,
      Next_Gate = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      Output = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // buttons
      // displays
      RGB_Current_Display = 0,
      RGB_Max_Display = 3,
      RGB_Min_Display = 6,
      RGB_Total_Display = 9,
      LIGHTS_LEN = 12
   };

};

#endif // NOT SelectPanelH
