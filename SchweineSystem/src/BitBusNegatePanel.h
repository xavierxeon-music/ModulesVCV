#ifndef BitBusNegatePanelH
#define BitBusNegatePanelH

#include "BitBusNegate.h"

struct BitBusNegate::Panel
{
   enum ParamId
   {
      Latch8,
      Latch7,
      Latch6,
      Latch5,
      Latch4,
      Latch3,
      Latch2,
      Latch1,
      PARAMS_LEN
   };

   enum InputId
   {
      GateIn8,
      GateIn7,
      GateIn6,
      GateIn5,
      GateIn4,
      GateIn3,
      GateIn2,
      GateIn1,
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
      Red_Latch8,
      Green_Latch8,
      Blue_Latch8,
      Red_Latch7,
      Green_Latch7,
      Blue_Latch7,
      Red_Latch6,
      Green_Latch6,
      Blue_Latch6,
      Red_Latch5,
      Green_Latch5,
      Blue_Latch5,
      Red_Latch4,
      Green_Latch4,
      Blue_Latch4,
      Red_Latch3,
      Green_Latch3,
      Blue_Latch3,
      Red_Latch2,
      Green_Latch2,
      Blue_Latch2,
      Red_Latch1,
      Green_Latch1,
      Blue_Latch1,
      LIGHTS_LEN
   };

};

#endif // NOT BitBusNegatePanelH
