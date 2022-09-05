#include "SvinKnob.h"

Svin::Knob::Knob(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
{
}

void Svin::Knob::setRange(const float& minValue, const float& maxValue, const bool& snap)
{
   rack::engine::ParamQuantity* knob = module->getParamQuantity(paramIndex);
   module->configParam(paramIndex, minValue, maxValue, 0.f, knob->name);
   if (snap)
      knob->snapEnabled = true;
}

float Svin::Knob::getValue() const
{
   const float value = module->params[paramIndex].getValue();
   return value;
}

void Svin::Knob::setValue(const float& value)
{
   module->params[paramIndex].setValue(value);
}