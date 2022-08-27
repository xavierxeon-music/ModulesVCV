#include "SvinButton.h"

#include "SvinModule.h"

Svin::Button::Button(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
   , trigger()
{
}

bool Svin::Button::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}
