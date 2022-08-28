#ifndef SvinDisplayOLEDH
#define SvinDisplayOLEDH

#include <rack.hpp>

#include "SvinCommon.h"
#include "SvinModule.h"
#include "SvinModuleWidget.h"

namespace Svin
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
         uint8_t width;
         uint8_t height;
      };

      class Controller : public PixelThing
      {
      public:
         Controller(Module* module, const uint16_t& pixelId);
         ~Controller();

      public:
         void fill(const Color& fillColor = Color{0, 0, 0}); // set all pixels to fill color

         void setColor(const Color& newColor);
         void drawPixel(const uint8_t x, const uint8_t y);
         void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
         void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill);
         void writeText(const uint8_t x, const uint8_t y, const std::string& text, const Font& font, const Alignment& alignment = Alignment::Left);

      private:
         friend class Widget;
         using IdMap = std::map<const uint16_t, Controller*>;
         using ControllerMap = std::map<Module*, IdMap>;

      private:
         static ControllerMap controllerMap;
         NVGcolor color;
      };

      class Widget : public rack::widget::Widget, public PixelThing
      {
      public:
         using ClickedFunction = std::function<void(const float& x, const float& y)>;

      public:
         Widget(rack::math::Vec pos, Module* module, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height);
         ~Widget();

      public:
         template <typename ClassType>
         void onClicked(ClassType* instance, void (ClassType::*functionPointer)(const float&, const float&));

         static Widget* find(Module* module, const uint16_t& pixelId);

      private:
         friend class Controller;
         using IdMap = std::map<const uint16_t, Widget*>;
         using WidgetMap = std::map<Module*, IdMap>;

      private:
         void drawLayer(const DrawArgs& args, int layer) override;
         void onButton(const rack::event::Button& buttonEvent) override;

      private:
         static WidgetMap widgetMap;
         std::vector<ClickedFunction> clickedFunctionList;
      };
   }; // namespace DisplayOLED
} // namespace Svin

inline void makeOLED(Svin::ModuleWidget* widget, rack::math::Vec pos, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height)
{
   rack::Widget* displayWidget = new Svin::DisplayOLED::Widget(pos, widget->getSchweineModule(), pixelId, width, height);
   widget->addChild(displayWidget);
}

#ifndef SvinDisplayOLEDHPP
#include "SvinDisplayOLED.hpp"
#endif // NOT SvinDisplayOLEDHPP

#endif // NOT SvinDisplayOLEDH
