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
         friend class Widget;
         using IdMap = std::map<const uint16_t, Controller*>;
         using ControllerMap = std::map<Module*, IdMap>;

      private:
         static ControllerMap controllerMap;
         Module* module;
         const uint16_t textId;
         const uint16_t rgbId;
      };

      class Widget : public rack::widget::Widget
      {
      public:
         Widget(rack::math::Vec pos, Module* module, const uint8_t& digitCount, const uint16_t& textId, const uint16_t& rgbId);

      public:
         const uint8_t& getFontSize() const;
         void setFontSize(const uint8_t size = 18);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;
         Controller* findController();

      private:
         Module* module;
         const uint8_t digitCount;
         const uint16_t textId;
         const uint16_t rgbId;
         std::shared_ptr<rack::Font> font;
         std::string fontPath;
         uint8_t fontSize;
      };
   } // namespace DisplayLCD
} // namespace Svin

inline void makeLCD(Svin::ModuleWidget* widget, rack::math::Vec pos, const uint8_t& digitCount, const uint16_t& textId, const uint16_t& rgbId)
{
   rack::Widget* displayWidget = new Svin::DisplayLCD::Widget(pos, widget->getSchweineModule(), digitCount, textId, rgbId);
   widget->addChild(displayWidget);
}

#endif // NOT SvinDisplayLCDH
