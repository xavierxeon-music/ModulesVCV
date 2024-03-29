#include "SvinLED.h"

#include "SvinModule.h"

Svin::LED::LED(Module* module, const uint16_t& rgbIndex)
   : module(module)
   , rgbIndex(rgbIndex)
   , defaultColor(Color::Predefined::White)
   , brightness(1.0)
{
}

void Svin::LED::setColor(const Color& color)
{
   const float red = static_cast<float>(color.red()) / 255.0;
   module->lights[rgbIndex + 0].setBrightness(red);

   const float green = static_cast<float>(color.green()) / 255.0;
   module->lights[rgbIndex + 1].setBrightness(green);

   const float blue = static_cast<float>(color.blue()) / 255.0;
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

   setColor(defaultColor.dim(brightness));
}
