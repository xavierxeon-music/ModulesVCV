#ifndef SvinButtonLEDH
#define SvinButtonLEDH

#include <SvinCommon.h>
#include <SvinLED.h>

namespace Svin
{
   class Module;
   class Input;

   class ButtonLED : private LED
   {
   public:
      using List = ElementList<ButtonLED>;

   public:
      ButtonLED(Module* module, const uint16_t& paramIndex, const uint16_t& rgbIndex);

   public:
      bool isTriggered();
      bool isLatched(const bool update = true);
      void setLatched(bool on);
      void setLatchBuddy(Input* input);

      using LED::setActive;
      using LED::setBrightness;
      using LED::setColor;
      using LED::setDefaultColor;
      using LED::setOff;
      using LED::setOn;

   private:
      uint16_t paramIndex;
      rack::dsp::BooleanTrigger trigger;
      bool latched;
      Input* latchBuddy;
   };

} // namespace Svin

inline void makeLEDButton(rack::ModuleWidget* widget, rack::math::Vec pos, int paramId, int firstLightId)
{
   rack::app::ParamWidget* paramWidget = rack::createLightParamCentered<rack::LEDLightButton<rack::LargeSimpleLight<rack::RedGreenBlueLight>>>(pos, widget->getModule(), paramId, firstLightId);
   widget->addParam(paramWidget);
}

#endif // NOT SvinButtonLEDH
