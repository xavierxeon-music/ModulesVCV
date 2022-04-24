#ifndef BitBusMeterAndFreezePanelH
#define BitBusMeterAndFreezePanelH

#include "BitBusMeterAndFreeze.h"

#include <SchweineSystemCommon.h>
#include <SchweineSystemLight.h>

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
      Red_Bit8_Status1,
      Green_Bit8_Status1,
      Blue_Bit8_Status1,
      Red_Bit7_Status1,
      Green_Bit7_Status1,
      Blue_Bit7_Status1,
      Red_Bit6_Status1,
      Green_Bit6_Status1,
      Blue_Bit6_Status1,
      Red_Bit5_Status1,
      Green_Bit5_Status1,
      Blue_Bit5_Status1,
      Red_Bit4_Status1,
      Green_Bit4_Status1,
      Blue_Bit4_Status1,
      Red_Bit3_Status1,
      Green_Bit3_Status1,
      Blue_Bit3_Status1,
      Red_Bit2_Status1,
      Green_Bit2_Status1,
      Blue_Bit2_Status1,
      Red_Bit1_Status1,
      Green_Bit1_Status1,
      Blue_Bit1_Status1,
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

   Panel();
};

#endif // NOT BitBusMeterAndFreezePanelH
