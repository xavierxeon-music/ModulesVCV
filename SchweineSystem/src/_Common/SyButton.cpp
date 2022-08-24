#include "SyButton.h"

#include "SyModule.h"

Sy::Button::Button(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
   , trigger()
{
}

bool Sy::Button::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}
