#include "SchweineSystemModule.h"

SchweineSystem::Module::Module()
   : rack::Module()
   , texts()
   , values()
   , pixels()
{
}

void SchweineSystem::Module::updateDisplays()
{
   // do nothing
}

void SchweineSystem::Module::configDisplay(const uint16_t& textId, std::string name)
{
   texts[textId] = std::string();
}

void SchweineSystem::Module::configMeter(const uint16_t& valueId, std::string name)
{
   values[valueId] = 0.0;
}

void SchweineSystem::Module::configPixels(const uint16_t& valueId, std::string name, const uint16_t& size)
{
   pixels[valueId] = new uint8_t[size];
}
