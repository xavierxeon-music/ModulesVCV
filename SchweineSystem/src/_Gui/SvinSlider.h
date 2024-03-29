#ifndef SvinSliderH
#define SvinSliderH

#include <rack.hpp>

#include <SvinCommon.h>
#include <SvinLED.h>

namespace Svin
{
   // 12 x 80
   class Slider : private LED
   {
   public:
      using List = ElementList<Slider>;

   public:
      Slider(Module* module, const uint16_t& paramIndex, const uint16_t& rgbIndex);

   public:
      void setRange(const float& minValue, const float& maxValue);                            // pre scale
      void setRange(const float& minValue, const float& maxValue, const float& defaultValue); // pre scale
      void enableSteps(bool enabled, const float& newScale = 1.0);
      float getValue() const;
      void setValue(const float& value);

      using LED::setActive;
      using LED::setBrightness;
      using LED::setColor;
      using LED::setDefaultColor;
      using LED::setOff;
      using LED::setOn;

   private:
      uint16_t paramIndex;
      float scale;
   };
} // namespace Svin

inline void makeSlider(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId, int firstLightId)
{
   rack::app::ParamWidget* paramWidget = nullptr;
   paramWidget = rack::createLightParamCentered<rack::VCVLightSlider<rack::RedGreenBlueLight>>(pos, widget->getModule(), paramId, firstLightId);
   widget->addParam(paramWidget);
}

#endif // NOT SvinSliderH
