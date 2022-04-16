#ifndef VCMCReceiverPanelH
#define VCMCReceiverPanelH

#include "VCMCReceiver.h"

struct VCMCReceiver::Panel
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
      OUTPUTS_LEN
   };

   enum LightId
   {
      LIGHTS_LEN
   };

};

#endif // NOT VCMCReceiverPanelH
