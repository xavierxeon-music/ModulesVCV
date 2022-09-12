#include "SvinButtonLED.h"

#include "SvinModule.h"

Svin::ButtonLED::ButtonLED(Module* module, const uint16_t& paramIndex, const uint16_t& rgbIndex)
   : LED(module, rgbIndex)
   , paramIndex(paramIndex)
   , trigger()
   , triggerBuddy(nullptr)
{
}

bool Svin::ButtonLED::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}

void Svin::ButtonLED::setTriggerBuddy(Input* input)
{
}
