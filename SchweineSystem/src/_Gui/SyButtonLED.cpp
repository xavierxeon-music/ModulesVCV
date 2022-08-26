#include "SyButtonLED.h"

#include "SyModule.h"

Sy::ButtonLED::ButtonLED(Module* module, const uint16_t& paramIndex, const uint16_t& rgbIndex)
   : LED(module, rgbIndex)
   , paramIndex(paramIndex)
   , trigger()
{
}

bool Sy::ButtonLED::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}

