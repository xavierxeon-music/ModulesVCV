#include "SvinDisplayOLED.h"

#include "SvinMaster.h"

// instructions

Svin::DisplayOLED::Controller::Instruction::Instruction(const NVGcolor& color)
   : color(color)
{
}

Svin::DisplayOLED::Controller::Instruction::~Instruction()
{
}

Svin::DisplayOLED::Controller::Pixel::Pixel(const NVGcolor& color, const uint8_t x, const uint8_t y)
   : Instruction(color)
   , x(x)
   , y(y)
{
}

void Svin::DisplayOLED::Controller::Pixel::draw(NVGcontext* context)
{
   nvgBeginPath(context);
   nvgRect(context, x + 1, y + 1, 1, 1);
   nvgFillColor(context, color);
   nvgFill(context);
}

Svin::DisplayOLED::Controller::Line::Line(const NVGcolor& color, const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2)
   : Instruction(color)
   , x1(x1)
   , y1(y1)
   , x2(x2)
   , y2(y2)
{
}

void Svin::DisplayOLED::Controller::Line::draw(NVGcontext* context)
{
   nvgBeginPath(context);
   nvgMoveTo(context, x1, y1);
   nvgLineTo(context, x2, y2);
   nvgStrokeWidth(context, 1.0);
   nvgStrokeColor(context, color);
   nvgStroke(context);
}

Svin::DisplayOLED::Controller::Rect::Rect(const NVGcolor& color, const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2)
   : Instruction(color)
   , x1(x1)
   , y1(y1)
   , x2(x2)
   , y2(y2)
{
}

void Svin::DisplayOLED::Controller::Rect::draw(NVGcontext* context)
{
   nvgBeginPath(context);
   const uint8_t width = x2 - x1;
   const uint8_t height = y2 - y1;
   nvgRect(context, x1 + 1, y1 + 1, width, height);
   nvgFillColor(context, color);
   nvgFill(context);
}

std::string Svin::DisplayOLED::Controller::Text::fontPath;

Svin::DisplayOLED::Controller::Text::Text(const NVGcolor& color, const uint8_t x, const uint8_t y, const std::string& text, const uint8_t fontSize)
   : Instruction(color)
   , x(x)
   , y(y)
   , text(text)
   , fontSize(fontSize)
   , font()
{
   if (fontPath.empty())
      fontPath = std::string(rack::asset::plugin(Master::the()->instance(), "res/fonts/FiraCode-Regular.ttf"));
}

void Svin::DisplayOLED::Controller::Text::draw(NVGcontext* context)
{
   if (!font)
      font = APP->window->loadFont(fontPath);

   nvgFontSize(context, fontSize);
   nvgFontFaceId(context, font->handle);

   nvgFillColor(context, color);
   nvgText(context, x, y + fontSize, text.c_str(), nullptr);
}

// controller

Svin::DisplayOLED::Controller::Controller(Module* module, const uint16_t& pixelId)
   : UiElement::ElementMap<Controller>(module, pixelId, this)
   , renderInstructions()
   , currentColor(nvgRGB(255, 255, 255))
   , width(1)
   , height(1)
   , clickedFunctionList()
{
}

void Svin::DisplayOLED::Controller::setColor(const Color& newColor)
{
   currentColor = nvgRGB(newColor.red, newColor.green, newColor.blue);
}

uint16_t Svin::DisplayOLED::Controller::compileIndex(const uint8_t x, const uint8_t y) const
{
   return x + (width * y);
}

void Svin::DisplayOLED::Controller::fill(const Color& fillColor)
{
   NVGcolor color = nvgRGB(fillColor.red, fillColor.green, fillColor.red);

   Rect* rect = new Rect(color, 0, 0, width, height);
   renderInstructions.push_back(rect);
}

void Svin::DisplayOLED::Controller::drawPixel(const uint8_t x, const uint8_t y)
{
   if (x >= width || y >= height)
      return;

   Pixel* instruction = new Pixel(currentColor, x, y);
   renderInstructions.push_back(instruction);
}

void Svin::DisplayOLED::Controller::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
   Line* instruction = new Line(currentColor, x1, y1, x2, y2);
   renderInstructions.push_back(instruction);
}

void Svin::DisplayOLED::Controller::drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill)
{
   if (fill)
   {
      Rect* instruction = new Rect(currentColor, x1, y1, x2, y2);
      renderInstructions.push_back(instruction);
   }
   else
   {
      drawLine(x1, y1, x2, y1);
      drawLine(x2, y1, x2, y2);
      drawLine(x2, y2, x1, y2);
      drawLine(x1, y2, x1, y1);
   }
}

void Svin::DisplayOLED::Controller::writeText(const uint8_t x, const uint8_t y, const std::string& text, const uint8_t& fontSize, const Alignment& alignment)
{
   Text* instruction = new Text(currentColor, x, y, text, fontSize);
   renderInstructions.push_back(instruction);
}

void Svin::DisplayOLED::Controller::clicked(const float& x, const float& y)
{
   for (ClickedFunction clickedFunction : clickedFunctionList)
      clickedFunction(x, y);
}

// widget

Svin::DisplayOLED::Widget::Widget(rack::math::Vec pos, Module* module, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height)
   : rack::widget::Widget()
   , UiElement::ElementMap<Controller>::Access(module, pixelId)
   , width(width)
   , height(height)
{
   box.pos = rack::math::Vec(pos.x, pos.y);

   Controller* controller = findElement();
   if (controller)
   {
      controller->width = width;
      controller->height = height;
   }
}


void Svin::DisplayOLED::Widget::drawLayer(const DrawArgs& args, int layer)
{
   if (layer != 1)
      return;

   const float padding = 0.1;
   const float pixelOffset = (1.0 - padding);
   const float pixelWidth = 1.0 + 2.0 * pixelOffset;

   Controller* controller = findElement();

   for (Controller::Instruction* instruction : controller->renderInstructions)
   {
      instruction->draw(args.vg);
      delete instruction;
   }
   controller->renderInstructions.clear();
}

void Svin::DisplayOLED::Widget::onButton(const rack::event::Button& buttonEvent)
{
   Controller* controller = findElement();
   if (!controller)
      return;

   if (0 > buttonEvent.pos.x || width <= buttonEvent.pos.x)
      return;
   if (0 > buttonEvent.pos.y || height <= buttonEvent.pos.y)
      return;

   if (GLFW_MOUSE_BUTTON_LEFT == buttonEvent.button && GLFW_PRESS == buttonEvent.action)
   {
      buttonEvent.consume(this);
      controller->clicked(buttonEvent.pos.x, buttonEvent.pos.y);
   }
}
