#ifndef SyButtonH
#define SyButtonH

#include <rack.hpp>

#include "SyCommon.h"

namespace Sy
{
   class Button
   {
   public:
      using List = ElementList<Button>;

   public:
      Button(Module* module, const uint16_t& paramIndex = 0);

   public:
      void assign(const uint16_t& paramIndex);
      bool isTriggered();

   private:
      Module* module;
      uint16_t paramIndex;
      rack::dsp::BooleanTrigger trigger;
   };
} // namespace Sy

inline void makeButton(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId)
{
   rack::app::ParamWidget* paramWidget = rack::createParamCentered<rack::TL1105>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

#endif // NOT SyButtonH
