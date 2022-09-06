#ifndef SvinSliderH
#define SvinSliderH

#include <rack.hpp>

#include "SvinCommon.h"

namespace Svin
{
   class Slider
   {
   public:
      using List = ElementList<Slider>;

   public:
      Slider(Module* module, const uint16_t& paramIndex);

   private:
      Module* module;
      uint16_t paramIndex;
   };
} // namespace Svin

inline void makeSlider(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId, bool horizontal)
{
   rack::app::ParamWidget* paramWidget = nullptr;
   if (horizontal)
      paramWidget = rack::createParamCentered<rack::LEDSliderWhite>(pos, widget->getModule(), paramId);
   else
      paramWidget = rack::createParamCentered<rack::LEDSliderWhite>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

#endif // NOT SvinSliderH
