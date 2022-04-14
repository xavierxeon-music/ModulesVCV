#ifndef BitBusBitOutPanelH
#define BitBusBitOutPanelH

#include "BitBusBitOut.h"

struct BitBusBitOut::Panel
{
   enum ParamId
   {
      PARAMS_LEN
   };

   enum InputId
   {
      INPUTS_LEN
   };

   enum OutputId
   {
      BitOut8,
      BitOut7,
      BitOut6,
      BitOut5,
      BitOut4,
      BitOut3,
      BitOut2,
      BitOut1,
      OUTPUTS_LEN
   };

   enum LightId
   {
      Red_BusIn,
      Green_BusIn,
      Blue_BusIn,
      LIGHTS_LEN
   };

};

#endif // BitBusBitOutPanelH
