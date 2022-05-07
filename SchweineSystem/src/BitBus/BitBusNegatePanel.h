#ifndef BitBusNegatePanelH
#define BitBusNegatePanelH

#include "BitBusNegate.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLED.h>

struct BitBusNegate::Panel
{
   enum ParamId
   {
      // buttons
      // switches
      // ledbuttons
      Bit8_Latch = 0,
      Bit7_Latch = 1,
      Bit6_Latch = 2,
      Bit5_Latch = 3,
      Bit4_Latch = 4,
      Bit3_Latch = 5,
      Bit2_Latch = 6,
      Bit1_Latch = 7,
      // knobs
      PARAMS_LEN = 8
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
      Bit8_GateIn = 0,
      Bit7_GateIn = 1,
      Bit6_GateIn = 2,
      Bit5_GateIn = 3,
      Bit4_GateIn = 4,
      Bit3_GateIn = 5,
      Bit2_GateIn = 6,
      Bit1_GateIn = 7,
      INPUTS_LEN = 8
   };

   enum OutputId
   {
      OUTPUTS_LEN = 0
   };

   enum LightId
   {
      // leds
      RGB_BusIn = 0,
      RGB_BusOut = 3,
      // ledbuttons
      RGB_Bit8_Latch = 6,
      RGB_Bit7_Latch = 9,
      RGB_Bit6_Latch = 12,
      RGB_Bit5_Latch = 15,
      RGB_Bit4_Latch = 18,
      RGB_Bit3_Latch = 21,
      RGB_Bit2_Latch = 24,
      RGB_Bit1_Latch = 27,
      // lcds
      LIGHTS_LEN = 30
   };

};

#endif // NOT BitBusNegatePanelH
