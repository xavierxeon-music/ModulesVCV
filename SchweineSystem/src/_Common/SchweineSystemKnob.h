#ifndef SchweineSystemKnobH
#define SchweineSystemKnobH

#include <rack.hpp>

namespace SchweineSystem
{
   class Knob
   {
   public:
      Knob();
   };
} // namespace SchweineSystem

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

#endif // NOT SchweineSystemKnobH
