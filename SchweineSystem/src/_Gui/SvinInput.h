#ifndef SvinInputH
#define SvinInputH

#include <rack.hpp>

#include <SvinCommon.h>

namespace Svin
{
   class Input
   {
   public:
      using List = ElementList<Input>;

   public:
      Input(Module* module, const uint16_t& inputIndex);

   public:
      bool isConnected() const;
      uint8_t getNumberOfChannels() const;
      // cv
      float getVoltage(const uint8_t channel = 0) const;
      // trigger
      bool isTriggered(const uint8_t channel = 0) const;
      // gate
      bool isOn(const uint8_t channel = 0) const;
      bool isOff(const uint8_t channel = 0) const;
      // threshold
      const float& getTriggerThreshold() const;
      void setTriggerThreshold(const float& value);

   private:
      Module* module;
      uint16_t inputIndex;
      float triggerThreshold;
      mutable rack::dsp::BooleanTrigger triggers[16];
   };
} // namespace Svin

inline void makeInput(rack::ModuleWidget* widget, rack::math::Vec pos, int inputId, bool poly = false)
{
   rack::app::PortWidget* portWidget = nullptr;
   if (poly)
      portWidget = rack::createInputCentered<rack::PJ3410Port>(pos, widget->getModule(), inputId);
   else
      portWidget = rack::createInputCentered<rack::PJ301MPort>(pos, widget->getModule(), inputId);
   widget->addInput(portWidget);
}

#endif // NOT SvinInputH
