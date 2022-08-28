#include "SvinDisplayLCD.h"

#include "SvinMaster.h"

// controller

Svin::DisplayLCD::Controller::Controller(Module* module, const uint16_t& displayId)
   : InstanceMap<Controller>(module, displayId, this)
   , text()
   , color()
{
}

Svin::DisplayLCD::Controller::~Controller()
{
}

void Svin::DisplayLCD::Controller::setText(const std::string& newText)
{
   text = newText;
}

void Svin::DisplayLCD::Controller::setColor(const Svin::Color& newColor)
{
   color = nvgRGB(newColor.red, newColor.green, newColor.blue);
}

// widget

Svin::DisplayLCD::Widget::Widget(rack::math::Vec pos, Module* module, const uint8_t& digitCount, const uint16_t& displayId, const uint8_t fontSize)
   : rack::widget::Widget()
   , InstanceMap<Controller>::Access(module, displayId)
   , digitCount(digitCount)
   , font()
   , fontPath()
   , fontSize(fontSize)
{
   fontPath = std::string(rack::asset::plugin(Master::the()->instance(), "res/fonts/Segment14.ttf"));
   box.pos = rack::math::Vec(pos.x + 2, pos.y + fontSize + 2);
}

void Svin::DisplayLCD::Widget::drawLayer(const DrawArgs& args, int layer)
{
   if (layer != 1)
      return;

   if (!font)
      font = APP->window->loadFont(fontPath);

   nvgFontSize(args.vg, fontSize);
   nvgFontFaceId(args.vg, font->handle);

   Controller* controller = findIntstance();
   if (!controller)
   {
      NVGcolor digitColor = nvgRGB(255, 25, 255);
      std::string placeholder = std::string(digitCount, '~');

      // lcd background
      nvgFillColor(args.vg, nvgTransRGBA(digitColor, 23));
      nvgText(args.vg, 1, 1, placeholder.c_str(), nullptr);

      return;
   }

   NVGcolor digitColor = controller->color;

   // lcd background
   nvgFillColor(args.vg, nvgTransRGBA(digitColor, 23));
   std::string placeholder = std::string(digitCount, '~');
   nvgText(args.vg, 1, 1, placeholder.c_str(), nullptr);

   // the value
   std::string valueString = controller->text;
   while (valueString.length() < digitCount)
      valueString = " " + valueString;

   nvgFillColor(args.vg, digitColor);
   nvgText(args.vg, 1, 1, valueString.c_str(), nullptr);
}
