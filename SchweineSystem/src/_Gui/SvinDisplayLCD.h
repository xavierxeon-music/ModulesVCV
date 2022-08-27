#ifndef SvinDisplayLCDH
#define SvinDisplayLCDH

#include <rack.hpp>

#include "SvinCommon.h"
#include "SvinModule.h"
#include "SvinModuleWidget.h"

namespace Svin
{
   namespace DisplayLCD
   {
      // 16 with per digit + 2 margin
      // 24 height
      class Controller
      {
      public:
         using List = TwoParamElementList<Controller>;

      public:
         Controller(Module* module, const uint16_t& textId, const uint16_t& rgbId);

      public:
         void setText(const std::string& text);
         void setColor(const Svin::Color& color);

      private:
         Module* module;
         const uint16_t textId;
         const uint16_t rgbId;
      };

      class Widget : public rack::TransparentWidget
      {
      public:
         Widget(rack::math::Vec pos, Module* module, const uint8_t& digitCount, const uint16_t& textId, const uint16_t& rgbId);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         Module* module;
         const uint8_t digitCount;
         const uint16_t textId;
         const uint16_t rgbId;
         std::shared_ptr<rack::Font> font;
         std::string fontPath;
      };
   } // namespace DisplayLCD
} // namespace Svin

inline void makeLCD(Svin::ModuleWidget* widget, rack::math::Vec pos, const uint8_t& digitCount, const uint16_t& textId, const uint16_t& rgbId)
{
   rack::Widget* displayWidget = new Svin::DisplayLCD::Widget(pos, widget->getSchweineModule(), digitCount, textId, rgbId);
   widget->addChild(displayWidget);
}

#endif // NOT SvinDisplayLCDH
