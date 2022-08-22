#ifndef BitBusMeterAndFreezePanelH
#define BitBusMeterAndFreezePanelH

#include "BitBusMeterAndFreeze.h"

#include <SyCommon.h>
#include <SyButtonLED.h>
#include <SyLED.h>

struct BitBusMeterAndFreeze::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      FlipSample = 0,
      FlipFreeze = 1,
      // knobs
      PARAMS_LEN = 2
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
      GateSample = 0,
      GateFreeze = 1,
      INPUTS_LEN = 2
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_Bit8_Status1 = 0,
      RGB_Bit7_Status1 = 3,
      RGB_Bit6_Status1 = 6,
      RGB_Bit5_Status1 = 9,
      RGB_Bit4_Status1 = 12,
      RGB_Bit3_Status1 = 15,
      RGB_Bit2_Status1 = 18,
      RGB_Bit1_Status1 = 21,
      RGB_BusIn = 24,
      RGB_BusOut = 27,
      // ledbuttons
      RGB_FlipSample = 30,
      RGB_FlipFreeze = 33,
      // lcds
      LIGHTS_LEN = 36
   };

};

#endif // NOT BitBusMeterAndFreezePanelH
