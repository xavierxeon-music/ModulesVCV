#ifndef BitifyPanelH
#define BitifyPanelH

#include "Bitify.h"

struct Bitify::Panel
{
   enum ParamId
   {
      FlipSwitch8,
      FlipSwitch7,
      FlipSwitch6,
      FlipSwitch5,
      FlipSwitch4,
      FlipSwitch3,
      FlipSwitch2,
      FlipSwitch1,
      PARAMS_LEN
   };

   enum InputId
   {
      AudioIn,
      Hold,
      BitIn8,
      GateIn8,
      BitIn7,
      GateIn7,
      BitIn6,
      GateIn6,
      BitIn5,
      GateIn5,
      BitIn4,
      GateIn4,
      BitIn3,
      GateIn3,
      BitIn2,
      GateIn2,
      BitIn1,
      GateIn1,
      INPUTS_LEN
   };

   enum OutputId
   {
      AudioOut,
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
      Light_FlipSwitch8,
      Light_FlipSwitch7,
      Light_FlipSwitch6,
      Light_FlipSwitch5,
      Light_FlipSwitch4,
      Light_FlipSwitch3,
      Light_FlipSwitch2,
      Light_FlipSwitch1,
      LIGHTS_LEN
   };

};

#endif // BitifyPanelH
