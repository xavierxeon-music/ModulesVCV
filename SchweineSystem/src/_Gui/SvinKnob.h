#ifndef SvinKnobH
#define SvinKnobH

#include <rack.hpp>

#include "SvinCommon.h"

namespace Svin
{
   class Knob
   {
   public:
      using List = ElementList<Knob>;

   public:
      Knob(Module* module, const uint16_t& paramIndex);

   public:
      void setRange(const float& minValue, const float& maxValue); // pre scale
      void enableSteps(bool enabled, const float& newScale = 1.0);
      float getValue() const;
      void setValue(const float& value);

   private:
      Module* module;
      uint16_t paramIndex;
      float scale;
   };
} // namespace Svin

inline void makeKnob(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId, uint8_t size = 1)
{
   rack::app::ParamWidget* paramWidget = nullptr;
   if (3 == size)
      paramWidget = rack::createParamCentered<rack::RoundHugeBlackKnob>(pos, widget->getModule(), paramId);
   else if (2 == size)
      paramWidget = rack::createParamCentered<rack::RoundBigBlackKnob>(pos, widget->getModule(), paramId);
   else
      paramWidget = rack::createParamCentered<rack::RoundSmallBlackKnob>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

#endif // NOT SvinKnobH
