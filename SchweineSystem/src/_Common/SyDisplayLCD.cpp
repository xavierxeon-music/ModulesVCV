#include "SyDisplayLCD.h"

#include "SyMaster.h"

// controller

Sy::DisplayLCD::Controller::Controller(Module* module, const uint16_t& textId, const uint16_t& rgbId)
   : module(module)
   , textId(textId)
   , rgbId(rgbId)
{
}

void Sy::DisplayLCD::Controller::setText(const std::string& text)
{
   module->texts[textId] = text;
}

void Sy::DisplayLCD::Controller::setColor(const Sy::Color& color)
{
   const float red = static_cast<float>(color.red) / 255.0;
   module->lights[rgbId + 0].setBrightness(red);

   const float green = static_cast<float>(color.green) / 255.0;
   module->lights[rgbId + 1].setBrightness(green);

   const float blue = static_cast<float>(color.blue) / 255.0;
   module->lights[rgbId + 2].setBrightness(blue);
}

// controller list

Sy::DisplayLCD::Controller::List::List(Module* module)
   : module(module)
{
}

Sy::DisplayLCD::Controller::List::~List()
{
   for (Controller* instance : instanceList)
      delete instance;
}

void Sy::DisplayLCD::Controller::List::append(const Params::List& paramsList)
{
   for (const Params& params : paramsList)
   {
      Controller* controller = new Controller(module, params.valueParamId, params.redLightId);
      instanceList.push_back(controller);
   }
}

Sy::DisplayLCD::Controller* Sy::DisplayLCD::Controller::List::operator[](const uint8_t& index)
{
   return instanceList[index];
}

// widget

Sy::DisplayLCD::Widget::Widget(rack::math::Vec pos, Module* module, const uint8_t& digitCount, const uint16_t& textId, const uint16_t& rgbId)
   : rack::TransparentWidget()
   , module(module)
   , digitCount(digitCount)
   , textId(textId)
   , rgbId(rgbId)
   , font()
   , fontPath()
{
   fontPath = std::string(rack::asset::plugin(Master::the()->instance(), "res/Segment14.ttf"));
   box.pos = rack::math::Vec(pos.x + 2, pos.y + 20);
}

void Sy::DisplayLCD::Widget::drawLayer(const DrawArgs& args, int layer)
{
   if (layer != 1)
      return;

   if (!font)
      font = APP->window->loadFont(fontPath);

   nvgFontSize(args.vg, 18);
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
