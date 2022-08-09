#ifndef MeshPathPanelH
#define MeshPathPanelH

#include "MeshPath.h"

#include <SchweineSystemCommon.h>

struct MeshPath::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      // knobs
      PARAMS_LEN = 0
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
      // lcds
      LIGHTS_LEN = 0
   };

};

#endif // NOT MeshPathPanelH
