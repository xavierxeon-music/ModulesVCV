#ifndef RevoicerPanelH
#define RevoicerPanelH

#include "Revoicer.h"

#include <SvinCommon.h>
#include <SvinButton.h>
#include <SvinDisplayLCD.h>
#include <SvinInput.h>
#include <SvinOutput.h>

struct Revoicer::Panel
{
   enum ParamId
   {
      // buttons
      Quality_Down = 0,
      Quality_Up = 1,
      // switches
      // ledbuttons
      // knobs
      PARAMS_LEN = 2
   };

   enum DisplayId
   {
      // lcd
      Text_Quality_Value = 0,
      // oled
      DISPLAYS_LEN = 1
   };

   enum MeterId
   {
      METERS_LEN = 0
   };

   enum InputId
   {
      AudioInput = 0,
      INPUTS_LEN = 1
   };

   enum OutputId
   {
      AudioOutput = 0,
      OUTPUTS_LEN = 1
   };

   enum LightId
   {
      // leds
      // ledbuttons
      // lcds
      RGB_Quality_Value = 0,
      LIGHTS_LEN = 3
   };

};

#endif // NOT RevoicerPanelH
