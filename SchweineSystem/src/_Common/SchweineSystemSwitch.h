#ifndef SchweineSystemSwitchH
#define SchweineSystemSwitchH

#include "SchweineSystemCommon.h"

namespace SchweineSystem
{
   class Switch
   {
   public:
      using List = ElementList<Switch>;

   public:
      Switch(Module* module, const uint16_t& paramIndex = 0);

   public:
      void assign(const uint16_t& paramIndex);
      void setState(bool on);
      bool isOn() const;
      bool isOff() const;

   private:
      Module* module;
      uint16_t paramIndex;
   };
} // namespace SchweineSystem

inline void makeSwitch(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId)
{
   rack::app::ParamWidget* paramWidget = rack::createParamCentered<rack::CKSS>(pos, widget->getModule(), paramId);
   widget->addParam(paramWidget);
}

#endif // NOT SchweineSystemSwitchH
