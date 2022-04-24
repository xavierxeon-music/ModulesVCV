#include "SchweineSystemModule.h"

SchweineSystem::Module::Module()
   : rack::Module()
   , texts()
   , values()
{
}

void SchweineSystem::Module::configDisplay(const uint16_t& textId, std::string name)
{
   texts[textId] = std::string();
}

void SchweineSystem::Module::configMeter(const uint16_t& valueId, std::string name)
{
   values[valueId] = 0.0;
}
