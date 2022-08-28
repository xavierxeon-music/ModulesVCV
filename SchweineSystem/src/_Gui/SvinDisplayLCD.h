#ifndef SvinDisplayLCDH
#define SvinDisplayLCDH

#include <rack.hpp>

#include "SvinCommon.h"
#include "SvinModule.h"
#include "SvinModuleWidget.h"
#include "SvinUiElement.h"

namespace Svin
{
   namespace DisplayLCD
   {
      // 16 with per digit + 2 margin
      // 24 height
      class Controller : public UiElement::Controller<Controller>
      {
      public:
         using List = ElementList<Controller>;

      public:
         Controller(Module* module, const uint16_t& displayId);
         ~Controller();

      public:
         void setText(const std::string& newText);
         void setColor(const Svin::Color& newColor);

      private:
         friend class Widget;

      private:
         std::string text;
         NVGcolor color;
      };

      class Widget : public rack::widget::Widget, private UiElement::View<Controller>
      {
      public:
         Widget(rack::math::Vec pos, Module* module, const uint8_t& digitCount, const uint16_t& displayId, const uint8_t fontSize = 18);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         const uint8_t digitCount;
         std::shared_ptr<rack::Font> font;
         std::string fontPath;
         uint8_t fontSize;
      };
   } // namespace DisplayLCD
} // namespace Svin

inline void makeLCD(Svin::ModuleWidget* widget, rack::math::Vec pos, const uint8_t& digitCount, const uint16_t& displayId)
{
   rack::Widget* displayWidget = new Svin::DisplayLCD::Widget(pos, widget->getSchweineModule(), digitCount, displayId);
   widget->addChild(displayWidget);
}

#endif // NOT SvinDisplayLCDH
