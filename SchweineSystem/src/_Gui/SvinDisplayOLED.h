#ifndef SvinDisplayOLEDH
#define SvinDisplayOLEDH

#include <rack.hpp>

#include <SvinCommon.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinUiElement.h>

namespace Svin
{
   // 1 pixel margin on all sides, hence size is (width + 2) by (height + 2)
   // default colors are white on black background
   namespace DisplayOLED
   {
      enum Font : uint8_t
      {
         Small = 8,   //  6 x  8
         Normal = 10, //  7 x 10
         Large = 18,  // 11 x 18
         Huge = 26,   // 16 x 26
      };

      enum class Alignment
      {
         Left,
         Center,
         Right
      };

      class Controller : public UiElement::ElementMap<Controller>
      {
      public:
         using ClickedFunction = std::function<void(const float& x, const float& y)>;

      public:
         Controller(Module* module, const uint16_t& pixelId);

      public:
         uint16_t compileIndex(const uint8_t x, const uint8_t y) const;
         void fill(const Color& fillColor = Color{0, 0, 0}); // set all pixels to fill color

         void setColor(const Color& newColor);
         void drawPixel(const uint8_t x, const uint8_t y);

         void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
         void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill);
         void writeText(const uint8_t x, const uint8_t y, const std::string& text, const uint8_t& fontSize, const Alignment& alignment = Alignment::Left);

         template <typename ClassType>
         void onClicked(ClassType* instance, void (ClassType::*functionPointer)(const float&, const float&));

      private:
         void clicked(const float& x, const float& y);

      private:
         class Instruction
         {
         public:
            using List = std::vector<Instruction*>;

         public:
            Instruction(const NVGcolor& color);
            virtual ~Instruction();

         public:
            virtual void draw(NVGcontext* context) = 0;

         protected:
            NVGcolor color;
         };

         class Pixel;
         class Line;
         class Rect;
         class Text;

         friend class Widget;

      private:
         Instruction::List renderInstructions;

         NVGcolor currentColor;
         uint8_t width;
         uint8_t height;

         std::vector<ClickedFunction> clickedFunctionList;
      };

      class Widget : public rack::widget::Widget, private UiElement::ElementMap<Controller>::Access
      {

      public:
         Widget(rack::math::Vec pos, Module* module, const uint16_t& pixelId, const uint8_t& width, const uint8_t& height);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;
         void onButton(const rack::event::Button& buttonEvent) override;

      private:
         uint8_t width;
         uint8_t height;

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
