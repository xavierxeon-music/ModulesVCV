#ifndef SvinKnobH
#define SvinKnobH

#include <rack.hpp>

/*
configParam(OCTAVE_PARAM, -5.0, 4.0, 0.0, "Octave", "'", 0.5);
getParamQuantity(OCTAVE_PARAM)->snapEnabled = true;
*/

namespace Svin
{
   class Knob
   {
   public:
      Knob();
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
