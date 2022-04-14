#ifndef BitBusBitInPanelH
#define BitBusBitInPanelH

#include "BitBusBitIn.h"

struct BitBusBitIn::Panel
{
   enum ParamId
   {
      PARAMS_LEN
   };

   enum InputId
   {
      BitIn8,
      BitIn7,
      BitIn6,
      BitIn5,
      BitIn4,
      BitIn3,
      BitIn2,
      BitIn1,
      INPUTS_LEN
   };

   enum OutputId
   {
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_BusOut,
      Green_BusOut,
      Blue_BusOut,
      Red_BusIn,
      Green_BusIn,
      Blue_BusIn,
      LIGHTS_LEN
   };

};

#endif // NOT BitBusBitInPanelH
