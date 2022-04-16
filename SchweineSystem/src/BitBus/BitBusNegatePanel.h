#ifndef BitBusNegatePanelH
#define BitBusNegatePanelH

#include "BitBusNegate.h"

struct BitBusNegate::Panel
{
   enum ParamId
   {
      Bit8_Latch,
      Bit7_Latch,
      Bit6_Latch,
      Bit5_Latch,
      Bit4_Latch,
      Bit3_Latch,
      Bit2_Latch,
      Bit1_Latch,
      PARAMS_LEN
   };

   enum InputId
   {
      Bit8_GateIn,
      Bit7_GateIn,
      Bit6_GateIn,
      Bit5_GateIn,
      Bit4_GateIn,
      Bit3_GateIn,
      Bit2_GateIn,
      Bit1_GateIn,
      INPUTS_LEN
   };

   enum OutputId
   {
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_BusIn,
      Green_BusIn,
      Blue_BusIn,
      Red_BusOut,
      Green_BusOut,
      Blue_BusOut,
      Red_Bit8_Latch,
      Green_Bit8_Latch,
      Blue_Bit8_Latch,
      Red_Bit7_Latch,
      Green_Bit7_Latch,
      Blue_Bit7_Latch,
      Red_Bit6_Latch,
      Green_Bit6_Latch,
      Blue_Bit6_Latch,
      Red_Bit5_Latch,
      Green_Bit5_Latch,
      Blue_Bit5_Latch,
      Red_Bit4_Latch,
      Green_Bit4_Latch,
      Blue_Bit4_Latch,
      Red_Bit3_Latch,
      Green_Bit3_Latch,
      Blue_Bit3_Latch,
      Red_Bit2_Latch,
      Green_Bit2_Latch,
      Blue_Bit2_Latch,
      Red_Bit1_Latch,
      Green_Bit1_Latch,
      Blue_Bit1_Latch,
      LIGHTS_LEN
   };

};

#endif // NOT BitBusNegatePanelH
