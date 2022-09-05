#include "SvinSwitch.h"

#include "SvinModule.h"

Svin::Switch::Switch(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
{
}

void Svin::Switch::setState(bool on)
{
   const float value = on ? 1.0 : 0.0;
   module->params[paramIndex].setValue(value);
}

bool Svin::Switch::isOn() const
{
   const bool on = (1.0 == module->params[paramIndex].getValue());
   return on;
}

bool Svin::Switch::isOff() const
{
   const bool on = (0.0 == module->params[paramIndex].getValue());
   return !on;
}
