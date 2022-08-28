#ifndef SvinLightMeterH
#define SvinLightMeterH

#include <rack.hpp>

#include <Tools/Range.h>

#include <SvinCommon.h>
#include <SvinModule.h>
#include <SvinModuleWidget.h>
#include <SvinUiElement.h>

namespace Svin
{
   namespace LightMeter
   {
      class Controller : public UiElement::ElementMap<Controller>
      {
      public:
         using List = ElementList<Controller>;

      public:
         Controller(Module* module, const uint16_t& valueId);

      public:
         void setMaxValue(const uint16_t& newMaxValue);
         void setValue(const uint32_t& newValue);

      private:
         friend class Widget;

      private:
         Range::Mapper valueMapper;
         uint32_t value;
      };

      class Widget : public rack::TransparentWidget, private UiElement::ElementMap<Controller>::Access
      {
      public:
         Widget(rack::math::Vec pos, Module* module, const uint8_t& segmentCount, const uint16_t& valueId);

      private:
         void drawLayer(const DrawArgs& args, int layer) override;

      private:
         const uint8_t segmentCount;
         Range::Mapper meterMapper;
      };
   } // namespace Meter
} // namespace Svin

inline void makeMeter(Svin::ModuleWidget* widget, rack::math::Vec pos, int digitCount, int paramId)
{
   rack::Widget* meterWidget = new Svin::LightMeter::Widget(pos, widget->getSchweineModule(), digitCount, paramId);
   widget->addChild(meterWidget);
}

#endif // NOT SvinLightMeterH
