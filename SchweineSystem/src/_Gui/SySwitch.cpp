#include "SySwitch.h"

#include "SyModule.h"

Sy::Switch::Switch(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
{
}


void Sy::Switch::setState(bool on)
{
   const float value = on ? 1.0 : 0.0;
   module->params[paramIndex].setValue(value);
}

bool Sy::Switch::isOn() const
{
   const bool on = module->params[paramIndex].getValue();
   return on;
}

bool Sy::Switch::isOff() const
{
   const bool on = module->params[paramIndex].getValue();
   return !on;
}
