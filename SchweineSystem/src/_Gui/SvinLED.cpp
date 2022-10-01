#include "SvinLED.h"

#include "SvinModule.h"

Svin::LED::LED(Module* module, const uint16_t& rgbIndex)
   : module(module)
   , rgbIndex(rgbIndex)
   , defaultColor(Color{255, 255, 255})
   , brightness(1.0)
{
}

void Svin::LED::setColor(const Color& color)
{
   const float red = static_cast<float>(color.red) / 255.0;
   module->lights[rgbIndex + 0].setBrightness(red);

   const float green = static_cast<float>(color.green) / 255.0;
   module->lights[rgbIndex + 1].setBrightness(green);

   const float blue = static_cast<float>(color.blue) / 255.0;
   module->lights[rgbIndex + 2].setBrightness(blue);
}

void Svin::LED::setDefaultColor(const Color& color)
{
   defaultColor = color;
}

void Svin::LED::setOn()
{
   setBrightness(1.0);
}

void Svin::LED::setOff()
{
   setBrightness(0.0);
}

void Svin::LED::setActive(bool on)
{
   if (on)
      setOn();
   else
      setOff();
}

void Svin::LED::setBrightness(const float newBrightness)
{
   if (newBrightness < 0.0)
      brightness = 0.0;
   else if (newBrightness > 1.0)
      brightness = 1.0;
   else
      brightness = newBrightness;

   const float fred = static_cast<float>(defaultColor.red) * brightness;
   const float fgreen = static_cast<float>(defaultColor.green) * brightness;
   const float fblue = static_cast<float>(defaultColor.blue) * brightness;

   const uint8_t red = static_cast<uint8_t>(fred);
   const uint8_t green = static_cast<uint8_t>(fgreen);
   const uint8_t blue = static_cast<uint8_t>(fblue);

   setColor(Color{red, green, blue});
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
