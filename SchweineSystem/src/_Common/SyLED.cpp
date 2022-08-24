#include "SyLED.h"

#include "SyModule.h"

Sy::LED::LED(Module* module, const uint16_t& rgbIndex)
   : module(module)
   , redIndex(rgbIndex + 0)
   , greenIndex(rgbIndex + 1)
   , blueIndex(rgbIndex + 2)
   , defaultColor(Sy::Color{255, 255, 255})
{
}

void Sy::LED::setColor(const Color& color)
{
   const float red = static_cast<float>(color.red) / 255.0;
   module->lights[redIndex].setBrightness(red);

   const float green = static_cast<float>(color.green) / 255.0;
   module->lights[greenIndex].setBrightness(green);

   const float blue = static_cast<float>(color.blue) / 255.0;
   module->lights[blueIndex].setBrightness(blue);
}

void Sy::LED::setDefaultColor(const Color& color)
{
   defaultColor = color;
}

void Sy::LED::setOn()
{
   setColor(defaultColor);
}

void Sy::LED::setOff()
{
   setColor({0, 0, 0});
}

void Sy::LED::setActive(bool on)
{
   if (on)
      setOn();
   else
      setOff();
}

// list

Sy::LED::List::List(Module* module)
   : module(module)
   , instanceList()
{
}

void Sy::LED::List::append(const std::vector<uint16_t>& rgbIndexList)
{
   for (const uint16_t rgbIndex : rgbIndexList)
   {
      LED led(module, rgbIndex);
      instanceList.push_back(led);
   }
}

Sy::LED* Sy::LED::List::operator[](const uint16_t& index)
{
   return &instanceList[index];
}
