#ifndef SchweineSystemLCDDisplayH
#define SchweineSystemLCDDisplayH

#include <rack.hpp>

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   namespace LCDDisplay
   {
      class Data
      {
      protected:
         Data(rack::engine::Module* module, const uint16_t& valueParamId, const uint16_t& redLightId);

      protected:
         rack::engine::Module* module;
         const uint16_t valueParamId;
         const uint16_t redLightId;
      };

      class Controller : public Data
      {
      public:
         class List;

      public:
         Controller(rack::engine::Module* module, const uint16_t& valueParamId, const uint16_t& redLightId);

      public:
         void setValue(const uint16_t& value);
         void setColor(const SchweineSystem::Color& color);
      };

      class Controller::List
      {
      public:
         using ParamMap = std::map<uint16_t, uint16_t>; // valueParam, redLight

      public:
         List(rack::engine::Module* module);
         ~List();

      public:
         void append(const ParamMap& paramMap);
         Controller* operator[](const uint16_t& index);

      private:
         rack::engine::Module* module;
         std::vector<Controller*> instanceList;
      };

      class Widget : public rack::TransparentWidget, public Data
      {
      public:
         Widget(rack::math::Vec pos, rack::engine::Module* module, const uint8_t& digitCount, const uint16_t& valueParamId, const uint16_t& redLightId);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         std::shared_ptr<rack::Font> font;
         std::string fontPath;
         const uint8_t digitCount;
      };
   } // namespace LCDDisplay
} // namespace SchweineSystem

#endif // NOT SchweineSystemLCDDisplayH
