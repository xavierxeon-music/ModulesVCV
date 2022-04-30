#ifndef SchweineSystemOLEDDisplayH
#define SchweineSystemOLEDDisplayH

#include <rack.hpp>

#include "SchweineSystemCommon.h"
#include "SchweineSystemModule.h"
#include "SchweineSystemModuleWidget.h"

namespace SchweineSystem
{
   // a 128x64 pixel black and white display (+1 pixel margin)
   namespace OLEDDisplay
   {
      struct Font
      {
         static Font Small;
         static Font Normal;
         static Font Large;
         static Font Huge;

         const uint8_t width;
         const uint8_t height;
         const uint16_t* data;
      };

      enum class Alignment
      {
         Left,
         Center,
         Right
      };

      class Controller
      {
      public:
         Controller(Module* module, const uint16_t& pixelId);

      public:
         void fill(bool on = false); // set all pixels to value
         void drawPixel(const uint8_t x, const uint8_t y, bool on = true);

         void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool on = true);
         void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill, bool on = true);

         void writeText(const uint8_t x, const uint8_t y, const std::string& text, const Font& font, bool on = true);
         static uint8_t compileLeftX(const uint8_t x, const std::string& text, const Font& font, const Alignment& alignment);

      private:
         void setCursor(uint8_t x, uint8_t y);
         char writeChar(char ch, Font font, bool on);

      private:
         Module* module;
         const uint16_t pixelId;
         uint8_t cursorX;
         uint8_t cursorY;
      };

      class Widget : public rack::TransparentWidget
      {
      public:
         Widget(rack::math::Vec pos, Module* module, const uint16_t& pixelId);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         Module* module;
         const uint16_t pixelId;
      };
   }; // namespace OLEDDisplay
} // namespace SchweineSystem

inline void makeDisplay(SchweineSystem::ModuleWidget* widget, rack::math::Vec pos, const uint16_t& pixelId)
{
   rack::Widget* displayWidget = new SchweineSystem::OLEDDisplay::Widget(pos, widget->getSchweineModule(), pixelId);
   widget->addChild(displayWidget);
}

#endif // NOT SchweineSystemOLEDDisplayH
