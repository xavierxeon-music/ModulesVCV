#ifndef SvinSwitchH
#define SvinSwitchH

#include <rack.hpp>

#include "SvinCommon.h"

namespace Svin
{
   class Switch
   {
   public:
      using List = OneParamElementList<Switch>;

   public:
      Switch(Module* module, const uint16_t& paramIndex = 0);

   public:
      void setState(bool on);
      bool isOn() const;
      bool isOff() const;

   private:
      Module* module;
      uint16_t paramIndex;
   };
} // namespace Svin

inline void makeSwitch(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId)
{
   rack::app::ParamWidget* paramWidget = rack::createParamCentered<rack::CKSS>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

#endif // NOT SvinSwitchH
