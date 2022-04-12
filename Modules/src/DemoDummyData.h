#ifndef DemoDummyDataH
#define DemoDummyDataH

#include "DemoDummy.h"

struct DemoDummy::Data
{
   enum ParamId
   {
      KNOB,
      PARAMS_LEN
   };

   enum InputId
   {
      INPUT1,
      INPUT2,
      INPUTS_LEN
   };

   enum OutputId
   {
      OUTPUT1,
      OUTPUT2,
      OUTPUTS_LEN
   };

   enum LightId
   {
      LIGHT,
      LIGHTS_LEN
   };

};

#endif // DemoDummyDataH
