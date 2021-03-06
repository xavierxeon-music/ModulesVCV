#ifndef SchweineSystemLightMeterH
#define SchweineSystemLightMeterH

#include <rack.hpp>

#include <Tools/Range.h>

#include <SchweineSystemCommon.h>
#include <SchweineSystemModule.h>
#include <SchweineSystemModuleWidget.h>

namespace SchweineSystem
{
   namespace LightMeter
   {
      class Controller
      {
      public:
         class List;

      public:
         Controller(Module* module, const uint16_t& valueId);

      public:
         void setMaxValue(const uint16_t& newMaxValue);
         void setValue(const uint32_t& value);

      private:
         Module* module;
         const uint16_t valueId;
         Range::Mapper valueMapper;
      };

      class Controller::List
      {
      public:
         List(Module* module);
         ~List();

      public:
         void append(const std::vector<uint16_t>& valueIdList);
         Controller* operator[](const uint16_t& index);

      private:
         Module* module;
         std::vector<Controller*> instanceList;
      };

      class Widget : public rack::TransparentWidget
      {
      public:
      public:
         Widget(rack::math::Vec pos, Module* module, const uint8_t& segmentCount, const uint16_t& valueId);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         Module* module;
         const uint16_t valueId;
         const uint8_t segmentCount;
         Range::Mapper meterMapper;
      };
   } // namespace Meter
} // namespace SchweineSystem

inline void makeMeter(SchweineSystem::ModuleWidget* widget, rack::math::Vec pos, int digitCount, int paramId)
{
   rack::Widget* meterWidget = new SchweineSystem::LightMeter::Widget(pos, widget->getSchweineModule(), digitCount, paramId);
   widget->addChild(meterWidget);
}

#endif // NOT SchweineSystemLightMeterH
