#include "SvinLED.h"

#include "SvinModule.h"

Svin::LED::LED(Module* module, const uint16_t& rgbIndex)
   : module(module)
   , redIndex(rgbIndex + 0)
   , greenIndex(rgbIndex + 1)
   , blueIndex(rgbIndex + 2)
   , defaultColor(Svin::Color{255, 255, 255})
{
}

void Svin::LED::setColor(const Color& color)
{
   const float red = static_cast<float>(color.red) / 255.0;
   module->lights[redIndex].setBrightness(red);

   const float green = static_cast<float>(color.green) / 255.0;
   module->lights[greenIndex].setBrightness(green);

   const float blue = static_cast<float>(color.blue) / 255.0;
   module->lights[blueIndex].setBrightness(blue);
}

void Svin::LED::setDefaultColor(const Color& color)
{
   defaultColor = color;
}

void Svin::LED::setOn()
{
   setColor(defaultColor);
}

void Svin::LED::setOff()
{
   setColor({0, 0, 0});
}

void Svin::LED::setActive(bool on)
{
   if (on)
      setOn();
   else
      setOff();
}

// list

Svin::LED::List::List(Module* module)
   : module(module)
   , instanceList()
{
}

void Svin::LED::List::append(const std::vector<uint16_t>& rgbIndexList)
{
   for (const uint16_t rgbIndex : rgbIndexList)
   {
      LED led(module, rgbIndex);
      instanceList.push_back(led);
   }
}

Svin::LED* Svin::LED::List::operator[](const uint16_t& index)
{
   return &instanceList[index];
}
