#ifndef BitBusCVInPanelH
#define BitBusCVInPanelH

#include "BitBusCVIn.h"

struct BitBusCVIn::Panel
{
   enum ParamId
   {
      PARAMS_LEN
   };

   enum InputId
   {
      CVIn,
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
      LIGHTS_LEN
   };

};

#endif // BitBusCVInPanelH
