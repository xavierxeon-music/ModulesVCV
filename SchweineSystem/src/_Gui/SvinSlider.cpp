#include "SvinSlider.h"

#include <SvinModule.h>

Svin::Slider::Slider(Module* module, const uint16_t& paramIndex, const uint16_t& rgbIndex)
   : LED(module, rgbIndex)
   , paramIndex(paramIndex)
   , scale(1.0)
{
}

void Svin::Slider::setRange(const float& minValue, const float& maxValue)
{
   rack::engine::ParamQuantity* knob = module->getParamQuantity(paramIndex);

   module->configParam(paramIndex, minValue, maxValue, minValue, knob->name);
}

void Svin::Slider::enableSteps(bool enabled, const float& newScale)
{
   rack::engine::ParamQuantity* knob = module->getParamQuantity(paramIndex);

   // unscale
   knob->minValue *= scale;
   knob->maxValue *= scale;

   // new scale
   scale = enabled ? newScale : 1.0;

   knob->minValue /= scale;
   knob->maxValue /= scale;

   knob->snapEnabled = enabled;
   knob->displayMultiplier = scale;
}

float Svin::Slider::getValue() const
{
   const float value = module->params[paramIndex].getValue();
   return value * scale;
}

void Svin::Slider::setValue(const float& value)
{
   module->params[paramIndex].setValue(value / scale);
}
