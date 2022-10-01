#include "SvinDisplayOLED.h"

#include <SvinOrigin.h>

// instructions

Svin::DisplayOLED::Controller::Instruction::Instruction(const NVGcolor& color)
   : color(color)
{
}

Svin::DisplayOLED::Controller::Instruction::~Instruction()
{
}

// pixel

class Svin::DisplayOLED::Controller::Instruction::Pixel : public Instruction
{
public:
   Pixel(const NVGcolor& color, const uint8_t x, const uint8_t y);

private:
   void draw(NVGcontext* context) override;

private:
   const uint8_t x;
   const uint8_t y;
};

Svin::DisplayOLED::Controller::Instruction::Pixel::Pixel(const NVGcolor& color, const uint8_t x, const uint8_t y)
   : Instruction(color)
   , x(x)
   , y(y)
{
}

void Svin::DisplayOLED::Controller::Instruction::Pixel::draw(NVGcontext* context)
{
   nvgBeginPath(context);
   nvgRect(context, x, y, 1, 1);
   nvgFillColor(context, color);
   nvgFill(context);
}

// line

class Svin::DisplayOLED::Controller::Instruction::Line : public Instruction
{
public:
   Line(const NVGcolor& color, const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2);

private:
   void draw(NVGcontext* context) override;

private:
   const uint8_t x1;
   const uint8_t y1;
   const uint8_t x2;
   const uint8_t y2;
};

Svin::DisplayOLED::Controller::Instruction::Line::Line(const NVGcolor& color, const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2)
   : Instruction(color)
   , x1(x1)
   , y1(y1)
   , x2(x2)
   , y2(y2)
{
}

void Svin::DisplayOLED::Controller::Instruction::Line::draw(NVGcontext* context)
{
   nvgBeginPath(context);
   nvgMoveTo(context, x1, y1);
   nvgLineTo(context, x2, y2);
   nvgStrokeWidth(context, 1.0);
   nvgStrokeColor(context, color);
   nvgStroke(context);
}

// rect

class Svin::DisplayOLED::Controller::Instruction::Rect : public Instruction
{
public:
   Rect(const NVGcolor& color, const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2);

private:
   void draw(NVGcontext* context) override;

private:
   const uint8_t x1;
   const uint8_t y1;
   const uint8_t x2;
   const uint8_t y2;
};

Svin::DisplayOLED::Controller::Instruction::Rect::Rect(const NVGcolor& color, const uint8_t x1, const uint8_t y1, const uint8_t x2, const uint8_t y2)
   : Instruction(color)
   , x1(x1)
   , y1(y1)
   , x2(x2)
   , y2(y2)
{
}

void Svin::DisplayOLED::Controller::Instruction::Rect::draw(NVGcontext* context)
{
   nvgBeginPath(context);
   const uint8_t width = x2 - x1;
   const uint8_t height = y2 - y1;
   nvgRect(context, x1 + 1, y1 + 1, width, height);
   nvgFillColor(context, color);
   nvgFill(context);
}

// text

class Svin::DisplayOLED::Controller::Instruction::Text : public Instruction
{
public:
   Text(const NVGcolor& color, const uint8_t x, const uint8_t y, const std::string& text, const uint8_t fontHeigth);

private:
   void draw(NVGcontext* context) override;

private:
   const uint8_t x;
   const uint8_t y;
   const std::string text;
   const uint8_t fontHeigth;

   std::shared_ptr<rack::Font> font;
   static std::string fontPath;
};

std::string Svin::DisplayOLED::Controller::Instruction::Text::fontPath;

Svin::DisplayOLED::Controller::Instruction::Text::Text(const NVGcolor& color, const uint8_t x, const uint8_t y, const std::string& text, const uint8_t fontHeigth)
   : Instruction(color)
   , x(x)
   , y(y)
   , text(text)
   , fontHeigth(fontHeigth)
   , font()
{
   if (fontPath.empty())
      fontPath = std::string(rack::asset::plugin(Origin::the()->instance(), "res/fonts/FiraCode-Regular.ttf"));
}

void Svin::DisplayOLED::Controller::Instruction::Text::draw(NVGcontext* context)
{
   if (!font)
      font = APP->window->loadFont(fontPath);

   nvgFontSize(context, 1.25 * fontHeigth); // pixel to point size
   nvgFontFaceId(context, font->handle);

   nvgFillColor(context, color);
   nvgText(context, x, y + (0.9 * fontHeigth), text.c_str(), nullptr);
}

// controller

Svin::DisplayOLED::Controller::Controller(Module* module, const uint16_t& pixelId)
   : InstanceMap<Controller>(module, pixelId, this)
   , renderInstructions()
   , currentColor(nvgRGB(255, 255, 255))
   , width(1)
   , height(1)
   , clickedFunctionList()
   , openFileList()
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

   Instruction::Rect* instruction = new Instruction::Rect(color, 0, 0, width, height);
   renderInstructions.push_back(instruction);
}

void Svin::DisplayOLED::Controller::drawPixel(const uint8_t x, const uint8_t y)
{
   if (x >= width || y >= height)
      return;

   Instruction::Pixel* instruction = new Instruction::Pixel(currentColor, x, y);
   renderInstructions.push_back(instruction);
}

void Svin::DisplayOLED::Controller::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
   Instruction::Line* instruction = new Instruction::Line(currentColor, x1, y1, x2, y2);
   renderInstructions.push_back(instruction);
}

void Svin::DisplayOLED::Controller::drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill)
{
   if (fill)
   {
      Instruction::Rect* instruction = new Instruction::Rect(currentColor, x1, y1, x2, y2);
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

void Svin::DisplayOLED::Controller::writeText(const uint8_t x, const uint8_t y, const std::string& text, const uint8_t& fontHeigth, const Alignment& alignment)
{
   const float offset = 0.5 * text.length() * fontHeigth;

   uint8_t textX = x;
   if (Alignment::Center == alignment)
      textX = x - (0.5 * offset);
   else if (Alignment::Right == alignment)
      textX = x - offset;

   Instruction::Text* instruction = new Instruction::Text(currentColor, textX, y, text, fontHeigth);
   renderInstructions.push_back(instruction);
}

void Svin::DisplayOLED::Controller::clicked(const float& x, const float& y)
{
   for (ClickedFunction& clickedFunction : clickedFunctionList)
      clickedFunction(x, y);

   for (OpenFile& openFile : openFileList)
   {
      const std::string fileName = module->getOpenFileName(openFile.filter);
      if (fileName.empty())
         continue;

      openFile.function(fileName);
   }
}

// widget

Svin::DisplayOLED::Widget::Widget(rack::math::Vec pos, Module* module, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height)
   : rack::widget::Widget()
   , InstanceMap<Controller>::Access(module, pixelId)
   , width(width)
   , height(height)
{
   box.pos = rack::math::Vec(pos.x, pos.y);

   Controller* controller = findIntstance();
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

   Controller* controller = findIntstance();
   if (!controller)
      return;

   for (Controller::Instruction* instruction : controller->renderInstructions)
   {
      instruction->draw(args.vg);
      delete instruction;
   }
   controller->renderInstructions.clear();
}

void Svin::DisplayOLED::Widget::onButton(const rack::event::Button& buttonEvent)
{
   Controller* controller = findIntstance();
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
