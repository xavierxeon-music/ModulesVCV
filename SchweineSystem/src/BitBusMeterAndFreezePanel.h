#ifndef BitBusMeterAndFreezePanelH
#define BitBusMeterAndFreezePanelH

#include "BitBusMeterAndFreeze.h"

struct BitBusMeterAndFreeze::Panel
{
   enum ParamId
   {
      FlipSample,
      FlipFreeze,
      PARAMS_LEN
   };

   enum InputId
   {
      GateSample,
      GateFreeze,
      INPUTS_LEN
   };

   enum OutputId
   {
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_Bit8,
      Green_Bit8,
      Blue_Bit8,
      Red_Bit7,
      Green_Bit7,
      Blue_Bit7,
      Red_Bit6,
      Green_Bit6,
      Blue_Bit6,
      Red_Bit5,
      Green_Bit5,
      Blue_Bit5,
      Red_Bit4,
      Green_Bit4,
      Blue_Bit4,
      Red_Bit3,
      Green_Bit3,
      Blue_Bit3,
      Red_Bit2,
      Green_Bit2,
      Blue_Bit2,
      Red_Bit1,
      Green_Bit1,
      Blue_Bit1,
      Red_BusIn,
      Green_BusIn,
      Blue_BusIn,
      Red_BusOut,
      Green_BusOut,
      Blue_BusOut,
      Red_FlipSample,
      Green_FlipSample,
      Blue_FlipSample,
      Red_FlipFreeze,
      Green_FlipFreeze,
      Blue_FlipFreeze,
      LIGHTS_LEN
   };

};

#endif // NOT BitBusMeterAndFreezePanelH
