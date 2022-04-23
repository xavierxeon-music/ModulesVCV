#ifndef SchweineSystemLCDDisplayH
#define SchweineSystemLCDDisplayH

#include <rack.hpp>

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   namespace LCDDisplay
   {
      class Controller
      {
      public:
         class List;

      public:
         Controller(rack::engine::Module* module, const uint16_t& valueParamId, const uint16_t& redLightId);

      public:
         void setValue(const uint32_t& value);
         void setColor(const SchweineSystem::Color& color);

      private:
         rack::engine::Module* module;
         const uint16_t valueParamId;
         const uint16_t redLightId;
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
         List(rack::engine::Module* module);
         ~List();

      public:
         void append(const Params::List& paramsList);
         Controller* operator[](const uint16_t& index);

      private:
         rack::engine::Module* module;
         std::vector<Controller*> instanceList;
      };

      class Widget : public rack::TransparentWidget
      {
      public:
         Widget(rack::math::Vec pos, rack::engine::Module* module, const uint8_t& digitCount, const uint16_t& valueParamId, const uint16_t& redLightId);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         rack::engine::Module* module;
         const uint8_t digitCount;
         const uint16_t valueParamId;
         const uint16_t redLightId;
         std::shared_ptr<rack::Font> font;
         std::string fontPath;
      };
   } // namespace LCDDisplay
} // namespace SchweineSystem

inline void makeDisplay(rack::ModuleWidget* widget, rack::math::Vec pos, int digitCount, int paramId, int firstLightId)
{
   rack::Widget* displayWidget = new SchweineSystem::LCDDisplay::Widget(pos, widget->getModule(), digitCount, paramId, firstLightId);
   widget->addChild(displayWidget);
}

#endif // NOT SchweineSystemLCDDisplayH
