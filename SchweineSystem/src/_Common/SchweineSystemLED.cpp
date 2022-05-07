#include "SchweineSystemLED.h"

#include "SchweineSystemModule.h"

SchweineSystem::LED::LED(Module* module, const uint16_t& rgbIndex)
   : module(module)
   , redIndex(rgbIndex + 0)
   , greenIndex(rgbIndex + 1)
   , blueIndex(rgbIndex + 2)
   , defaultColor{255, 255, 255}
{
}

void SchweineSystem::LED::assign(const uint16_t& rgbIndex)
{
   redIndex = rgbIndex + 0;
   greenIndex = rgbIndex + 1;
   blueIndex = rgbIndex + 2;
}

void SchweineSystem::LED::setColor(const Color& color)
{
   const float red = static_cast<float>(color.red) / 255.0;
   module->lights[redIndex].setBrightness(red);

   const float green = static_cast<float>(color.green) / 255.0;
   module->lights[greenIndex].setBrightness(green);

   const float blue = static_cast<float>(color.blue) / 255.0;
   module->lights[blueIndex].setBrightness(blue);
}

void SchweineSystem::LED::setDefaultColor(const Color& color)
{
   defaultColor = color;
}

void SchweineSystem::LED::setOn()
{
   setColor(defaultColor);
}

void SchweineSystem::LED::setOff()
{
   setColor({0, 0, 0});
}

// list

SchweineSystem::LED::List::List(Module* module)
   : module(module)
   , instanceList()
{
}

void SchweineSystem::LED::List::append(const std::vector<uint16_t>& rgbIndexList)
{
   for (const uint16_t rgbIndex : rgbIndexList)
   {
      LED led(module, rgbIndex);
      instanceList.push_back(led);
   }
}

SchweineSystem::LED* SchweineSystem::LED::List::operator[](const uint16_t& index)
{
   return &instanceList[index];
}
