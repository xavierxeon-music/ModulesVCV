#include "SyButton.h"

#include "SyModule.h"

Sy::Button::Button(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
   , trigger()
{
}

void Sy::Button::assign(const uint16_t& newParamIndex)
{
   paramIndex = newParamIndex;
}

bool Sy::Button::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}
