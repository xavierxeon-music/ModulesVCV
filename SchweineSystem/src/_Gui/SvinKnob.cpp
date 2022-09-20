#include "SvinKnob.h"

#include <SvinModule.h>

Svin::Knob::Knob(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
   , scale(1.0)
{
}

void Svin::Knob::setRange(const float& minValue, const float& maxValue)
{
   setRange(minValue, maxValue, minValue);
}

void Svin::Knob::setRange(const float& minValue, const float& maxValue, const float& defaultValue)
{
   rack::engine::ParamQuantity* knob = module->getParamQuantity(paramIndex);

   module->configParam(paramIndex, minValue, maxValue, defaultValue, knob->name);
}

void Svin::Knob::enableSteps(bool enabled, const float& setpSize)
{
   rack::engine::ParamQuantity* knob = module->getParamQuantity(paramIndex);

   // unscale
   knob->minValue *= scale;
   knob->maxValue *= scale;
   knob->defaultValue *= scale;

   // new scale
   scale = enabled ? setpSize : 1.0;

   knob->minValue /= scale;
   knob->maxValue /= scale;
   knob->defaultValue /= scale;

   knob->snapEnabled = enabled;
   knob->displayMultiplier = scale;
}

float Svin::Knob::getValue() const
{
   const float value = module->params[paramIndex].getValue();
   return value * scale;
}

void Svin::Knob::setValue(const float& value)
{
   module->params[paramIndex].setValue(value / scale);
}
