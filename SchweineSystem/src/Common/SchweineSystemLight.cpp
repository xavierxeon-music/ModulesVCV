#include "SchweineSystemLight.h"

SchweineSystem::Light::Light(std::vector<rack::engine::Light>& fullList)
   : fullList(fullList)
   , redIndex(0)
   , greenIndex(0)
   , blueIndex(0)
   , defaultColor{255, 255, 255}
{
}

void SchweineSystem::Light::assign(const uint16_t& redIndex)
{
   this->redIndex = redIndex + 0;
   greenIndex = redIndex + 1;
   blueIndex = redIndex + 2;
}

void SchweineSystem::Light::setDefaultColor(const Color& color)
{
   defaultColor = color;
}

void SchweineSystem::Light::setColor(const Color& color)
{
   const float red = static_cast<float>(color.red) / 255.0;
   fullList[redIndex].setBrightness(red);

   const float green = static_cast<float>(color.green) / 255.0;
   fullList[greenIndex].setBrightness(green);

   const float blue = static_cast<float>(color.blue) / 255.0;
   fullList[blueIndex].setBrightness(blue);
}

void SchweineSystem::Light::setOn()
{
   setColor(defaultColor);
}

void SchweineSystem::Light::setOff()
{
   setColor({0, 0, 0});
}

// list

SchweineSystem::Light::List::List(std::vector<rack::engine::Light>& fullList)
   : fullList(fullList)
   , instanceList()
{
}

void SchweineSystem::Light::List::append(std::vector<uint16_t> redIndexList)
{
   for (const uint16_t redIndex : redIndexList)
   {
      Light light(fullList);
      light.assign(redIndex);
      instanceList.push_back(light);
   }
}

SchweineSystem::Light* SchweineSystem::Light::List::operator[](const uint16_t& index)
{
   return &instanceList[index];
}
