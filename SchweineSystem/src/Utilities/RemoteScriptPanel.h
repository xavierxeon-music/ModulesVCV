#ifndef RemoteScriptPanelH
#define RemoteScriptPanelH

#include "RemoteScript.h"

#include <SvinCommon.h>
#include <SvinButton.h>
#include <SvinLED.h>
#include <SvinDisplayOLED.h>

struct RemoteScript::Panel
{
   enum ParamId
   {
      // buttons
      Kill = 0,
      Restart = 1,
      // switches
      // ledbuttons
      // knobs
      // sliders
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
      INPUTS_LEN = 0
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_Connected = 0,
      // ledbuttons
      // sliders
      LIGHTS_LEN = 3
   };

};

#endif // NOT RemoteScriptPanelH
