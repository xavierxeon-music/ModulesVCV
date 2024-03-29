#ifndef SvinDisplayOLEDH
#define SvinDisplayOLEDH

#include <rack.hpp>

#include <MusicTools.h>

#include <SvinCommon.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>

namespace Svin
{
   // 1 pixel margin on all sides, hence size is (width + 2) by (height + 2)
   // default colors are white on black background
   namespace DisplayOLED
   {
      enum Font : uint8_t
      {
         Small = 8,
         Normal = 10,
         Large = 18,
         Huge = 26
      };

      enum class Alignment
      {
         Left,
         Center,
         Right
      };

      class Controller : public InstanceMap<Controller>
      {
      public:
         using List = ElementList<Controller>;
         using ClickedFunction = std::function<void(const float& x, const float& y)>;

      public:
         Controller(Module* module, const uint16_t& pixelId);

      public:
         uint16_t compileIndex(const uint8_t x, const uint8_t y) const;
         void fill(const Color& fillColor = Color::Predefined::Black); // set all pixels to fill color

         void setColor(const Color& newColor);
         void drawPixel(const uint8_t x, const uint8_t y);

         void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
         void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill);
         void writeText(const uint8_t x, const int16_t y, const std::string& text, const uint8_t& fontHeigth, const Alignment& alignment = Alignment::Left);

         void onPressed(ClickedFunction clickedFunction);
         void onReleased(ClickedFunction clickedFunction);

         template <typename ClassType>
         void onPressed(ClassType* instance, void (ClassType::*functionPointer)(const float&, const float&));

         template <typename ClassType>
         void onPressedOpenFileFunction(ClassType* instance, void (ClassType::*functionPointer)(const std::string& fileName), const std::string& filter);

      private:
         void pressed(const float& x, const float& y);
         void released(const float& x, const float& y);

      private:
         class Instruction
         {
         public:
            using List = std::vector<Instruction*>;
            class Pixel;
            class Line;
            class Rect;
            class Text;

         public:
            Instruction(const NVGcolor& color);
            virtual ~Instruction();

         public:
            virtual void draw(NVGcontext* context) = 0;

         protected:
            NVGcolor color;
         };


         struct OpenFile
         {
            using Function = std::function<void(const std::string& fileName)>;

            Function function;
            const std::string filter;

            using List = std::vector<OpenFile>;
         };

         friend class Widget;

      private:
         Instruction::List renderInstructions;

         NVGcolor currentColor;
         uint8_t width;
         uint8_t height;

         std::vector<ClickedFunction> pressedFunctionList;
         std::vector<ClickedFunction> releasedFunctionList;
         OpenFile::List openFileList;
      };

      class Widget : public rack::widget::Widget, private InstanceMap<Controller>::Access
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
