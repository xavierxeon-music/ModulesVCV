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
      Red_FlipSwitch8,
      Green_FlipSwitch8,
      Blue_FlipSwitch8,
      Red_FlipSwitch7,
      Green_FlipSwitch7,
      Blue_FlipSwitch7,
      Red_FlipSwitch6,
      Green_FlipSwitch6,
      Blue_FlipSwitch6,
      Red_FlipSwitch5,
      Green_FlipSwitch5,
      Blue_FlipSwitch5,
      Red_FlipSwitch4,
      Green_FlipSwitch4,
      Blue_FlipSwitch4,
      Red_FlipSwitch3,
      Green_FlipSwitch3,
      Blue_FlipSwitch3,
      Red_FlipSwitch2,
      Green_FlipSwitch2,
      Blue_FlipSwitch2,
      Red_FlipSwitch1,
      Green_FlipSwitch1,
      Blue_FlipSwitch1,
      LIGHTS_LEN
   };

};

#endif // BitifyPanelH
