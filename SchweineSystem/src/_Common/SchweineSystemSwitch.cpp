#include "SchweineSystemSwitch.h"

#include "SchweineSystemModule.h"

SchweineSystem::Switch::Switch(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
{
}

void SchweineSystem::Switch::assign(const uint16_t& newParamIndex)
{
   paramIndex = newParamIndex;
}

void SchweineSystem::Switch::setState(bool on)
{
   const float value = on ? 1.0 : 0.0;
   module->params[paramIndex].setValue(value);
}

bool SchweineSystem::Switch::isOn()
{
   const bool on = module->params[paramIndex].getValue();
   return on;
}
