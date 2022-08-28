#include "SvinDisplayLCD.h"

#include "SvinMaster.h"

// controller

Svin::DisplayLCD::Controller::Controller(Module* module, const uint16_t& textId, const uint16_t& rgbId)
   : module(module)
   , textId(textId)
   , rgbId(rgbId)
{
}

void Svin::DisplayLCD::Controller::setText(const std::string& text)
{
   module->texts[textId] = text;
}

void Svin::DisplayLCD::Controller::setColor(const Svin::Color& color)
{
   const float red = static_cast<float>(color.red) / 255.0;
   module->lights[rgbId + 0].setBrightness(red);

   const float green = static_cast<float>(color.green) / 255.0;
   module->lights[rgbId + 1].setBrightness(green);

   const float blue = static_cast<float>(color.blue) / 255.0;
   module->lights[rgbId + 2].setBrightness(blue);
}

// widget

Svin::DisplayLCD::Widget::Widget(rack::math::Vec pos, Module* module, const uint8_t& digitCount, const uint16_t& textId, const uint16_t& rgbId)
   : rack::widget::Widget()
   , module(module)
   , digitCount(digitCount)
   , textId(textId)
   , rgbId(rgbId)
   , font()
   , fontPath()
   , fontSize(18)
{
   fontPath = std::string(rack::asset::plugin(Master::the()->instance(), "res/fonts/Segment14.ttf"));
   box.pos = rack::math::Vec(pos.x + 2, pos.y + fontSize + 2);
}

const uint8_t& Svin::DisplayLCD::Widget::getFontSize() const
{
   return fontSize;
}

void Svin::DisplayLCD::Widget::setFontSize(const uint8_t size)
{
   fontSize = size;
}

void Svin::DisplayLCD::Widget::drawLayer(const DrawArgs& args, int layer)
{
   if (layer != 1)
      return;

   if (!font)
      font = APP->window->loadFont(fontPath);

   nvgFontSize(args.vg, fontSize);
   nvgFontFaceId(args.vg, font->handle);
   //nvgTextLetterSpacing(args.vg, 2.5);

   NVGcolor digitColor = [&]()
   {
      if (!module)
         return nvgRGB(255, 25, 255);

      const float red = 255.0 * module->lights[rgbId + 0].getBrightness();
      const float green = 255.0 * module->lights[rgbId + 1].getBrightness();
      const float blue = 255.0 * module->lights[rgbId + 2].getBrightness();

      return nvgRGB(red, green, blue);
   }();

   std::string placeholder = std::string(digitCount, '~');
   std::string valueString = module ? module->texts[textId] : std::string("");
   while (valueString.length() < digitCount)
      valueString = " " + valueString;

   // lcd background
   nvgFillColor(args.vg, nvgTransRGBA(digitColor, 23));
   nvgText(args.vg, 1, 1, placeholder.c_str(), nullptr);

   // the value
   nvgFillColor(args.vg, digitColor);
   nvgText(args.vg, 1, 1, valueString.c_str(), nullptr);
}
