#ifndef RemoteScriptPanelH
#define RemoteScriptPanelH

#include "RemoteScript.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemButtonLED.h>
#include <SchweineSystemDisplayOLED.h>

struct RemoteScript::Panel
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
      Pixels_Display = 0,
      DISPLAYS_LEN = 1
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

#endif // NOT RemoteScriptPanelH
