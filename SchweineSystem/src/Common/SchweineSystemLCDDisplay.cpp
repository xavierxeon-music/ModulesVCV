#include "SchweineSystemLCDDisplay.h"

#include "SchweineSystemMaster.h"

static union
{
   float value;
   struct
   {
      uint8_t alpha;
      uint8_t red;
      uint8_t green;
      uint8_t blue;
   };
} convert;

// data

SchweineSystem::LCDDisplay::Data::Data(rack::engine::Module* module, const uint16_t& valueParamId)
   : module(module)
   , valueParamId(valueParamId)
{
   convert.alpha = 0;
}

// controller

SchweineSystem::LCDDisplay::Controller::Controller(rack::engine::Module* module, const uint16_t& valueParamId)
   : Data(module, valueParamId)
{
}

void SchweineSystem::LCDDisplay::Controller::setValue(const uint16_t& value)
{
   module->params[valueParamId].setValue(static_cast<float>(value));
   const float fValue = module->params[valueParamId].getValue();
}

void SchweineSystem::LCDDisplay::Controller::setColor(const SchweineSystem::Color& color)
{
   convert.red = color.red;
   convert.green = color.green;
   convert.blue = color.blue;

   module->params[valueParamId + 1].setValue(convert.value);
}

// controller list

SchweineSystem::LCDDisplay::Controller::List::List(rack::engine::Module* module)
   : module(module)
{
}

SchweineSystem::LCDDisplay::Controller::List::~List()
{
   for (Controller* instance : instanceList)
      delete instance;
}

void SchweineSystem::LCDDisplay::Controller::List::append(const std::vector<uint16_t>& valueParamIdLists)
{
   for (const uint16_t& valueParamId : valueParamIdLists)
   {
      Controller* controller = new Controller(module, valueParamId);
      instanceList.push_back(controller);
   }
}

SchweineSystem::LCDDisplay::Controller* SchweineSystem::LCDDisplay::Controller::List::operator[](const uint16_t& index)
{
   return instanceList[index];
}

// widget

SchweineSystem::LCDDisplay::Widget::Widget(rack::math::Vec pos, rack::engine::Module* module, const uint8_t& digitCount, const uint16_t& valueParamId)
   : rack::TransparentWidget()
   , Data(module, valueParamId)
   , font()
   , fontPath()
   , digitCount(digitCount)
{
   fontPath = std::string(rack::asset::plugin(Master::the()->instance(), "res/Segment14.ttf"));
   box.pos = rack::math::Vec(pos.x + 2, pos.y + 20);
}

void SchweineSystem::LCDDisplay::Widget::drawLayer(const DrawArgs& args, int layer)
{
   if (layer != 1)
      return;

   if (!font)
      font = APP->window->loadFont(fontPath);

   nvgFontSize(args.vg, 18);
   nvgFontFaceId(args.vg, font->handle);
   //nvgTextLetterSpacing(args.vg, 2.5);

   NVGcolor digitColor = [&]
   {
      if (!module)
         return nvgRGB(255, 25, 255);

      convert.value = module->params[valueParamId + 1].getValue();
      return nvgRGB(convert.red, convert.green, convert.blue);
   }();

   std::string placeholder = std::string(digitCount, '~');

   std::string valueString = [&]
   {
      if (!module)
         return std::string("");

      const float fValue = module->params[valueParamId].getValue();
      const uint8_t value = static_cast<uint8_t>(fValue);

      return std::to_string(value);
   }();

   while (valueString.length() < digitCount)
      valueString = " " + valueString;

   // lcd background
   nvgFillColor(args.vg, nvgTransRGBA(digitColor, 23));
   nvgText(args.vg, 1, 1, placeholder.c_str(), nullptr);

   // the value
   nvgFillColor(args.vg, digitColor);
   nvgText(args.vg, 1, 1, valueString.c_str(), NULL);
}
