#ifndef SyButtonLEDH
#define SyButtonLEDH

#include "SyCommon.h"
#include "SyLED.h"

namespace Sy
{
   class Module;

   class ButtonLED : private LED
   {
   public:
      using List = TwoParamElementList<ButtonLED>;

   public:
      ButtonLED(Module* module, const uint16_t& paramIndex = 0, const uint16_t& rgbIndex = 0);

   public:
      void assign(const uint16_t& paramIndex, const uint16_t& rgbIndex);
      bool isTriggered();

      using LED::setActive;
      using LED::setColor;
      using LED::setDefaultColor;
      using LED::setOff;
      using LED::setOn;

   private:
      uint16_t paramIndex;
      rack::dsp::BooleanTrigger trigger;
   };

} // namespace Sy

inline void makeLEDButton(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId, int firstLightId)
{
   rack::app::ParamWidget* paramWidget = rack::createLightParamCentered<rack::LEDLightButton<rack::LargeSimpleLight<rack::RedGreenBlueLight>>>(pos, widget->getModule(), paramId, firstLightId);
   widget->addParam(paramWidget);
}

#endif // NOT SyButtonLEDH
