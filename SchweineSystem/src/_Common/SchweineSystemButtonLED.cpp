#include "SchweineSystemButtonLED.h"

#include "SchweineSystemModule.h"

SchweineSystem::ButtonLED::ButtonLED(Module* module, const uint16_t& paramIndex, const uint16_t& rgbIndex)
   : LED(module, rgbIndex)
   , paramIndex(paramIndex)
   , trigger()
{
}

void SchweineSystem::ButtonLED::assign(const uint16_t& newParamIndex, const uint16_t& rgbIndex)
{
   paramIndex = newParamIndex;
   LED::assign(rgbIndex);
}

bool SchweineSystem::ButtonLED::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}

// list

SchweineSystem::ButtonLED::List::List(Module* module)
   : module(module)
   , instanceList()
{
}

void SchweineSystem::ButtonLED::List::append(const Params::List& paramsList)
{
   for (const Params& params : paramsList)
   {
      ButtonLED button(module, params.paramIndex, params.rgbIndex);
      instanceList.push_back(button);
   }
}

SchweineSystem::ButtonLED* SchweineSystem::ButtonLED::List::operator[](const uint16_t& index)
{
   return &instanceList[index];
}
