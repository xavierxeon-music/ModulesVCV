#ifndef SvinOutputH
#define SvinOutputH

#include <rack.hpp>

#include "SvinCommon.h"

namespace Svin
{
   class Output
   {
   public:
      using List = ElementList<Output>;

   public:
      Output(Module* module, const uint16_t& outputIndex = 0);

   public:
      bool isConnected() const;
      uint8_t getNumberOfChannels() const;
      void setNumberOfChannels(const uint8_t count);
      // cv
      float getVoltage(const uint8_t channel = 0) const;
      void setVoltage(const float& value, const uint8_t channel = 0);
      // trigger
      void trigger(const uint8_t channel = 0);
      bool animateTriggers(const rack::Module::ProcessArgs& args); // trigger is active
      // gate
      void setOn(const uint8_t channel = 0);
      void setOff(const uint8_t channel = 0);
      void setActive(bool on, const uint8_t channel = 0);

   private:
      Module* module;
      uint16_t outputIndex;
      rack::dsp::PulseGenerator pulses[16];
   };
} // namespace Svin

inline void makeOutput(rack::ModuleWidget* widget, rack::math::Vec pos, int outputId, bool poly = false)
{
   rack::app::PortWidget* portWidget = nullptr;
   if (poly)
      portWidget = rack::createOutputCentered<rack::PJ3410Port>(pos, widget->getModule(), outputId);
   else
      portWidget = rack::createOutputCentered<rack::PJ301MPort>(pos, widget->getModule(), outputId);
   widget->addOutput(portWidget);
}

#endif // NOT SvinOutputH
