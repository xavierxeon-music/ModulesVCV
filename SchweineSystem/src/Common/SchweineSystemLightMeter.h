#ifndef SchweineSystemLightMeterH
#define SchweineSystemLightMeterH

#include <rack.hpp>

#include <Tools/Range.h>

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   namespace LightMeter
   {
      class Controller
      {
      public:
         class List;

      public:
         Controller(rack::engine::Module* module, const uint16_t& valueParamId);

      public:
         void setMaxValue(const uint16_t& newMaxValue);
         void setValue(const uint32_t& value);

      private:
         rack::engine::Module* module;
         const uint16_t valueParamId;
         Range::Mapper valueMapper;
      };

      class Controller::List
      {
      public:
         List(rack::engine::Module* module);
         ~List();

      public:
         void append(const std::vector<uint16_t>& paramIdList);
         Controller* operator[](const uint16_t& index);

      private:
         rack::engine::Module* module;
         std::vector<Controller*> instanceList;
      };

      class Widget : public rack::TransparentWidget
      {
      public:
      public:
         Widget(rack::math::Vec pos, rack::engine::Module* module, const uint8_t& segmentCount, const uint16_t& valueParamId);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         rack::engine::Module* module;
         const uint16_t valueParamId;
         const uint8_t segmentCount;
         Range::Mapper meterMapper;
      };
   } // namespace Meter
} // namespace SchweineSystem

inline void makeMeter(rack::ModuleWidget* widget, rack::math::Vec pos, int digitCount, int paramId)
{
   rack::Widget* meterWidget = new SchweineSystem::LightMeter::Widget(pos, widget->getModule(), digitCount, paramId);
   widget->addChild(meterWidget);
}

#endif // NOT SchweineSystemLightMeterH
