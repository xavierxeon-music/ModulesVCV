#ifndef SchweineSystemDisplayOLEDH
#define SchweineSystemDisplayOLEDH

#include <rack.hpp>

#include "SchweineSystemCommon.h"
#include "SchweineSystemModule.h"
#include "SchweineSystemModuleWidget.h"

namespace SchweineSystem
{
   // 1 pixel margin on all sides, hence size is (width + 2) by (height + 2)
   // default colors are white on black background
   namespace DisplayOLED
   {
      struct Font
      {
         static Font Small;  //  6 x  8
         static Font Normal; //  7 x 10
         static Font Large;  // 11 x 18
         static Font Huge;   // 16 x 26

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

      class PixelThing
      {
      public:
         PixelThing(Module* module, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height);

      protected:
         uint16_t compileIndex(const uint8_t x, const uint8_t y) const;

      protected:
         Module* module;
         const uint16_t pixelId;
         const uint8_t width;
         const uint8_t height;
      };

      class Controller : public PixelThing
      {
      public:
         Controller(Module* module, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height);

      public:
         void fill(const Color& fillColor = Color{0, 0, 0}); // set all pixels to fill color

         void setColor(const Color& newColor);
         void drawPixel(const uint8_t x, const uint8_t y);
         void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
         void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill);
         void writeText(const uint8_t x, const uint8_t y, const std::string& text, const Font& font, const Alignment& alignment = Alignment::Left);

      private:
         NVGcolor color;
      };

      class Widget : public rack::TransparentWidget, public PixelThing
      {
      public:
         Widget(rack::math::Vec pos, Module* module, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;
      };
   }; // namespace DisplayOLED
} // namespace SchweineSystem

inline void makeOLED(SchweineSystem::ModuleWidget* widget, rack::math::Vec pos, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height)
{
   rack::Widget* displayWidget = new SchweineSystem::DisplayOLED::Widget(pos, widget->getSchweineModule(), pixelId, width, height);
   widget->addChild(displayWidget);
}

#endif // NOT SchweineSystemDisplayOLEDH
