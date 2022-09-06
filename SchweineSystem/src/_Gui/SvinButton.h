#ifndef SvinButtonH
#define SvinButtonH

#include <rack.hpp>

#include "SvinCommon.h"

namespace Svin
{
   class Button
   {
   public:
      using List = ElementList<Button>;

   public:
      Button(Module* module, const uint16_t& paramIndex);

   public:
      bool isTriggered();

   private:
      Module* module;
      uint16_t paramIndex;
      rack::dsp::BooleanTrigger trigger;
   };
} // namespace Svin

inline void makeButton(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId)
{
   rack::app::ParamWidget* paramWidget = rack::createParamCentered<rack::TL1105>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

#endif // NOT SvinButtonH
