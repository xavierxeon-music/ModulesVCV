#ifndef SvinDisplayLCDH
#define SvinDisplayLCDH

#include <rack.hpp>

#include <SvinCommon.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>


namespace Svin
{
   namespace DisplayLCD
   {
      // 16 with per digit + 2 margin
      // 24 height
      class Controller : public InstanceMap<Controller>
      {
      public:
         using List = ElementList<Controller>;

      public:
         Controller(Module* module, const uint16_t& displayId);
         ~Controller();

      public:
         void setText(const std::string& newText);
         void setColor(const Color& newColor);

      private:
         friend class Widget;

      private:
         std::string text;
         NVGcolor color;
      };

      class Widget : public rack::widget::Widget, private InstanceMap<Controller>::Access
      {
      public:
         Widget(rack::math::Vec pos, Module* module, const uint8_t& digitCount, const uint16_t& displayId, const uint8_t fontSize);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         const uint8_t digitCount;
         std::shared_ptr<rack::Font> font;
         std::string fontPath;
         const uint8_t fontSize;
      };
   } // namespace DisplayLCD
} // namespace Svin

inline void makeLCD(Svin::ModuleWidget* widget, rack::math::Vec pos, const uint8_t& digitCount, const uint16_t& displayId, const uint8_t fontSize)
{
   rack::Widget* displayWidget = new Svin::DisplayLCD::Widget(pos, widget->getSchweineModule(), digitCount, displayId, fontSize);
   widget->addChild(displayWidget);
}

#endif // NOT SvinDisplayLCDH
