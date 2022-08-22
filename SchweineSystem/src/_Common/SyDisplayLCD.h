#ifndef SyDisplayLCDH
#define SyDisplayLCDH

#include <rack.hpp>

#include "SyCommon.h"
#include "SyModule.h"
#include "SyModuleWidget.h"

namespace Sy
{
   namespace DisplayLCD
   {
      // 16 with per digit + 2 margin
      // 24 height
      class Controller
      {
      public:
         class List;

      public:
         Controller(Module* module, const uint16_t& textId, const uint16_t& rgbId);

      public:
         void setText(const std::string& text);
         void setColor(const Sy::Color& color);

      private:
         Module* module;
         const uint16_t textId;
         const uint16_t rgbId;
      };

      class Controller::List
      {
      public:
         struct Params
         {
            uint16_t valueParamId;
            uint16_t redLightId;

            using List = std::vector<Params>;
         };

      public:
         List(Module* module);
         ~List();

      public:
         void append(const Params::List& paramsList);
         Controller* operator[](const uint8_t& index);

      private:
         Module* module;
         std::vector<Controller*> instanceList;
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
} // namespace Sy

inline void makeLCD(Sy::ModuleWidget* widget, rack::math::Vec pos, const uint8_t& digitCount, const uint16_t& textId, const uint16_t& rgbId)
{
   rack::Widget* displayWidget = new Sy::DisplayLCD::Widget(pos, widget->getSchweineModule(), digitCount, textId, rgbId);
   widget->addChild(displayWidget);
}

#endif // NOT SyDisplayLCDH
