#include "SchweineSystemLCDDisplay.h"

#include "SchweineSystemMaster.h"

SchweineSystem::LCDDisplay::LCDDisplay()
   : rack::TransparentWidget()
   , font()
   , fontPath()
   , digitColor(nvgRGB(255, 255, 255))
   , numberOfDigits(3)
   , value(nullptr)
{
   fontPath = std::string(rack::asset::plugin(Master::the()->instance(), "res/Segment14.ttf"));
}

void SchweineSystem::LCDDisplay::setup(uint16_t* value, const uint8_t& numberOfDigits)
{
   this->numberOfDigits = numberOfDigits;
   this->value = value;
}

void SchweineSystem::LCDDisplay::setPosition(uint16_t x, uint16_t y)
{
   box.pos = rack::Vec(x, y + 18);
}

void SchweineSystem::LCDDisplay::setDigitColor(const Color& color)
{
   digitColor = nvgRGB(color.red, color.green, color.blue);
}

void SchweineSystem::LCDDisplay::drawLayer(const DrawArgs& args, int layer)
{
   if (layer != 1)
      return;

   if (!font)
      font = APP->window->loadFont(fontPath);

   nvgFontSize(args.vg, 18);
   nvgFontFaceId(args.vg, font->handle);
   //nvgTextLetterSpacing(args.vg, 2.5);

   // lcd background
   nvgFillColor(args.vg, nvgTransRGBA(digitColor, 23));
   std::string placeholder = std::string(3, '~');
   nvgText(args.vg, 1, 1, placeholder.c_str(), nullptr);

   // the value
   nvgFillColor(args.vg, digitColor);
   std::string valueString = value ? std::to_string(*value) : "666";
   while (valueString.length() < numberOfDigits)
      valueString = " " + valueString;
   nvgText(args.vg, 1, 1, valueString.c_str(), NULL);
}
