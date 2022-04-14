#ifndef BitBusCVOutPanelH
#define BitBusCVOutPanelH

#include "BitBusCVOut.h"

struct BitBusCVOut::Panel
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
      CVOut,
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

#endif // BitBusCVOutPanelH
