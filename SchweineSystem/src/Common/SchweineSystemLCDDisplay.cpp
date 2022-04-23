#include "SchweineSystemLCDDisplay.h"

#include "SchweineSystemMaster.h"

// data

SchweineSystem::LCDDisplay::Data::Data(rack::engine::Module* module, const uint16_t& valueParamId, const uint16_t& redLightId)
   : module(module)
   , valueParamId(valueParamId)
   , redLightId(redLightId)
{
}

// controller

SchweineSystem::LCDDisplay::Controller::Controller(rack::engine::Module* module, const uint16_t& valueParamId, const uint16_t& redLightId)
   : Data(module, valueParamId, redLightId)
{
}

void SchweineSystem::LCDDisplay::Controller::setValue(const uint32_t& value)
{
   module->params[valueParamId].setValue(static_cast<float>(value));
}

void SchweineSystem::LCDDisplay::Controller::setColor(const SchweineSystem::Color& color)
{
   const float red = static_cast<float>(color.red) / 255.0;
   module->lights[redLightId + 0].setBrightness(red);

   const float green = static_cast<float>(color.green) / 255.0;
   module->lights[redLightId + 1].setBrightness(green);

   const float blue = static_cast<float>(color.blue) / 255.0;
   module->lights[redLightId + 2].setBrightness(blue);
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

void SchweineSystem::LCDDisplay::Controller::List::append(const Params::List& paramsList)
{
   for (const Params& params : paramsList)
   {
      Controller* controller = new Controller(module, params.valueParamId, params.redLightId);
      instanceList.push_back(controller);
   }
}

SchweineSystem::LCDDisplay::Controller* SchweineSystem::LCDDisplay::Controller::List::operator[](const uint16_t& index)
{
   return instanceList[index];
}

// widget

SchweineSystem::LCDDisplay::Widget::Widget(rack::math::Vec pos, rack::engine::Module* module, const uint8_t& digitCount, const uint16_t& valueParamId, const uint16_t& redLightId)
   : rack::TransparentWidget()
   , Data(module, valueParamId, redLightId)
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

      const float red = 255.0 * module->lights[redLightId + 0].getBrightness();
      const float green = 255.0 * module->lights[redLightId + 1].getBrightness();
      const float blue = 255.0 * module->lights[redLightId + 2].getBrightness();

      return nvgRGB(red, green, blue);
   }();

   std::string placeholder = std::string(digitCount, '~');

   std::string valueString = [&]
   {
      if (!module)
         return std::string("");

      const float fValue = module->params[valueParamId].getValue();
      const uint32_t value = static_cast<uint32_t>(fValue); // use 32 bit to avoid buffer overflow

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
