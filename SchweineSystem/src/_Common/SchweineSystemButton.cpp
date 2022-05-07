#include "SchweineSystemButton.h"

#include "SchweineSystemModule.h"

SchweineSystem::Button::Button(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
   , trigger()
{
}

void SchweineSystem::Button::assign(const uint16_t& newParamIndex)
{
   paramIndex = newParamIndex;
}

bool SchweineSystem::Button::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}
