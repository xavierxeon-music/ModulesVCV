#ifndef SchweineSystemButtonLEDH
#define SchweineSystemButtonLEDH

#include "SchweineSystemCommon.h"
#include "SchweineSystemLED.h"

namespace SchweineSystem
{
   class Module;

   class ButtonLED : private LED
   {
   public:
      class List;

   public:
      ButtonLED(Module* module, const uint16_t& paramIndex = 0, const uint16_t& rgbIndex = 0);

   public:
      void assign(const uint16_t& paramIndex, const uint16_t& rgbIndex);
      bool isTriggered();

      using LED::setColor;
      using LED::setDefaultColor;
      using LED::setOff;
      using LED::setOn;

   private:
      uint16_t paramIndex;
      rack::dsp::BooleanTrigger trigger;
   };

   class ButtonLED::List
   {
   public:
      struct Params
      {
         const uint16_t paramIndex;
         const uint16_t rgbIndex;

         using List = std::vector<Params>;
      };

   public:
      List(Module* module);

   public:
      void append(const Params::List& paramsList);
      ButtonLED* operator[](const uint16_t& index);

   private:
      Module* module;
      std::vector<ButtonLED> instanceList;
   };

} // namespace SchweineSystem

#endif // NOT SchweineSystemButtonLEDH
