#include "SyButtonLED.h"

#include "SyModule.h"

Sy::ButtonLED::ButtonLED(Module* module, const uint16_t& paramIndex, const uint16_t& rgbIndex)
   : LED(module, rgbIndex)
   , paramIndex(paramIndex)
   , trigger()
{
}

void Sy::ButtonLED::assign(const uint16_t& newParamIndex, const uint16_t& rgbIndex)
{
   paramIndex = newParamIndex;
   LED::assign(rgbIndex);
}

bool Sy::ButtonLED::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}

// list

Sy::ButtonLED::List::List(Module* module)
   : module(module)
   , instanceList()
{
}

void Sy::ButtonLED::List::append(const Params::List& paramsList)
{
   for (const Params& params : paramsList)
   {
      ButtonLED button(module, params.paramIndex, params.rgbIndex);
      instanceList.push_back(button);
   }
}

Sy::ButtonLED* Sy::ButtonLED::List::operator[](const uint16_t& index)
{
   return &instanceList[index];
}
