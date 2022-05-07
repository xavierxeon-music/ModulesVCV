#include "SchweineSystemButton.h"

#include "SchweineSystemModule.h"

SchweineSystem::Button::Button(Module* module, const uint16_t& paramIndex)
   : module(module)
   , paramIndex(paramIndex)
   , trigger()
{
}

void SchweineSystem::Button::assign(const uint16_t& newParamIndex)
{
   paramIndex = newParamIndex;
}

bool SchweineSystem::Button::isTriggered()
{
   const bool pressed = module->params[paramIndex].getValue();
   return trigger.process(pressed);
}

// list

SchweineSystem::Button::List::List(Module* module)
   : module(module)
   , instanceList()
{
}

void SchweineSystem::Button::List::append(const std::vector<uint16_t>& paramIndexList)
{
   for (const uint16_t paramIndex : paramIndexList)
   {
      Button button(module, paramIndex);
      instanceList.push_back(button);
   }
}

SchweineSystem::Button* SchweineSystem::Button::List::operator[](const uint16_t& index)
{
   return &instanceList[index];
}
